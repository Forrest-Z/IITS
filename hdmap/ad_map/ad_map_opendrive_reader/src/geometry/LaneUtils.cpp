/*
 * ----------------- BEGIN LICENSE BLOCK ---------------------------------
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * ----------------- END LICENSE BLOCK -----------------------------------
 */

#include "opendrive/geometry/LaneUtils.hpp"

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <iostream>
#include <vector>

#include "opendrive/geometry/Geometry.h"

namespace opendrive {
namespace geometry {

typedef ::boost::geometry::model::d2::point_xy<double> Boost2dPoint;
typedef ::boost::geometry::model::polygon<Boost2dPoint> BoostPolygon;

/**
 * Convert lane to boost polygon
 *
 * move the lane edges by the given margin to the center (shrink the lane)
 */
BoostPolygon fromLane(Lane const &lane, double const margin) {
  auto const &leftBorder = lane.leftEdge;
  auto const &rightBorder = lane.rightEdge;

  std::vector<Boost2dPoint> leftPoints;
  std::vector<Boost2dPoint> rightPoints;

  for (auto it = leftBorder.begin(); it != leftBorder.end(); ++it) {
    Boost2dPoint point({it->x, it->y});
    // leave out consecutive identical points
    if (leftPoints.empty() ||
        (boost::geometry::distance(leftPoints.back(), point) > 0.001)) {
      leftPoints.push_back(point);
    }
  }
  for (auto it = rightBorder.begin(); it != rightBorder.end(); ++it) {
    Boost2dPoint point({it->x, it->y});
    // leave out consecutive identical points
    if (rightPoints.empty() ||
        (boost::geometry::distance(rightPoints.back(), point) > 0.001)) {
      rightPoints.push_back(point);
    }
  }

  Boost2dPoint orthogonalDirection;
  size_t i = 0;
  if (leftPoints.size() > 1) {
    for (; i < leftPoints.size() - 1; i++) {
      Boost2dPoint direction = leftPoints[i + 1];
      boost::geometry::subtract_point(direction, leftPoints[i]);
      double normalizingFactor =
          1.0 / boost::geometry::distance(leftPoints[i + 1], leftPoints[i]);
      Boost2dPoint normalizedDirection = direction;
      boost::geometry::multiply_value(normalizedDirection, normalizingFactor);

      orthogonalDirection.x(normalizedDirection.y());
      orthogonalDirection.y(-normalizedDirection.x());
      boost::geometry::multiply_value(orthogonalDirection, margin);
      boost::geometry::add_point(leftPoints[i], orthogonalDirection);
    }
    boost::geometry::add_point(leftPoints[i], orthogonalDirection);
  }

  if (rightPoints.size() > 1) {
    i = 0;
    for (; i < rightPoints.size() - 1; i++) {
      Boost2dPoint direction = rightPoints[i + 1];
      boost::geometry::subtract_point(direction, rightPoints[i]);
      double normalizingFactor =
          1.0 / boost::geometry::distance(rightPoints[i + 1], rightPoints[i]);
      Boost2dPoint normalizedDirection = direction;
      boost::geometry::multiply_value(normalizedDirection, normalizingFactor);

      orthogonalDirection.x(-normalizedDirection.y());
      orthogonalDirection.y(normalizedDirection.x());
      boost::geometry::multiply_value(orthogonalDirection, margin);
      boost::geometry::add_point(rightPoints[i], orthogonalDirection);
    }
    boost::geometry::add_point(rightPoints[i], orthogonalDirection);
  }

  std::vector<Boost2dPoint> points = leftPoints;
  // insert the right points in vice versa direction
  points.insert(points.end(), rightPoints.rbegin(), rightPoints.rend());
  // close polygon
  points.push_back(points.front());
  BoostPolygon polygon;
  ::boost::geometry::assign_points(polygon, points);
  // ensure that all polygons have the same orientation
  ::boost::geometry::correct(polygon);
  return polygon;
}

void invertLane(Lane &lane) {
  std::reverse(lane.leftEdge.begin(), lane.leftEdge.end());
  std::reverse(lane.rightEdge.begin(), lane.rightEdge.end());
  std::swap(lane.leftEdge, lane.rightEdge);
  std::swap(lane.leftNeighbor, lane.rightNeighbor);
  std::swap(lane.predecessors, lane.successors);
  lane.index = -lane.index;

  for (auto &signalReference : lane.signalReferences) {
    signalReference.inLaneOrientation = !signalReference.inLaneOrientation;
    signalReference.parametricPosition =
        1.0 - signalReference.parametricPosition;
  }

  for (auto &parametricSpeed : lane.speed) {
    auto start = 1.0 - parametricSpeed.end;
    auto end = 1.0 - parametricSpeed.start;
    parametricSpeed.end = end;
    parametricSpeed.start = start;
  }
}

ContactPlace contactPlace(Lane const &leftLane, Lane const &rightLane) {
  if (leftLane.leftEdge.empty() || leftLane.rightEdge.empty()) {
    std::cerr << "Empty left lane " << leftLane.id << "\n";
    return ContactPlace::None;
  }
  if (rightLane.leftEdge.empty() || rightLane.rightEdge.empty()) {
    std::cerr << "Empty right lane " << leftLane.id << "\n";
    return ContactPlace::None;
  }
  auto const thisLeftStart = leftLane.leftEdge.front();
  auto const thisRightStart = leftLane.rightEdge.front();
  auto const otherLeftStart = rightLane.leftEdge.front();
  auto const otherRightStart = rightLane.rightEdge.front();

  auto const thisLeftEnd = leftLane.leftEdge.back();
  auto const thisRightEnd = leftLane.rightEdge.back();
  auto const otherLeftEnd = rightLane.leftEdge.back();
  auto const otherRightEnd = rightLane.rightEdge.back();

  if ((near(thisLeftStart, otherLeftStart) &&
       near(thisLeftEnd, otherLeftEnd)) ||
      (near(thisRightStart, otherRightStart) &&
       near(thisRightEnd, otherRightEnd))) {
    return ContactPlace::Overlap;
  } else if (near(thisLeftStart, otherRightStart) &&
             near(thisLeftEnd, otherRightEnd)) {
    return ContactPlace::LeftRight;
  } else if (near(thisLeftStart, otherLeftEnd) &&
             near(thisLeftEnd, otherLeftStart)) {
    return ContactPlace::LeftLeft;
  } else if (near(thisRightStart, otherLeftStart) &&
             near(thisRightEnd, otherLeftEnd)) {
    return ContactPlace::RightLeft;
  } else if (near(thisRightStart, otherRightEnd) &&
             near(thisRightEnd, otherRightStart)) {
    return ContactPlace::RightRight;
  }

  return ContactPlace::None;
}

Id laneId(int roadId, int laneSectionIndex, int laneIndex) {
  if (roadId < 0) {
    std::cerr << "Invalid road id " << roadId << "\n";
  }

  if (laneSectionIndex < 0) {
    std::cerr << "Invalid lane section index" << roadId << "\n";
  }

  Id road = static_cast<Id>(roadId) * 100000;
  Id lane = static_cast<Id>(laneIndex) + 50;
  Id laneSection = static_cast<Id>(laneSectionIndex) * 100;

  return road + laneSection + lane;
}

bool lanesOverlap(Lane const &leftLane, Lane const &rightLane,
                  double const overlapMargin) {
  if (leftLane.id == rightLane.id) {
    return true;
  }
  if ((leftLane.type != LaneType::Driving) ||
      (rightLane.type != LaneType::Driving)) {
    return false;
  }

  try {
    auto leftPolygon = fromLane(leftLane, overlapMargin);
    auto rightPolygon = fromLane(rightLane, overlapMargin);
    std::deque<BoostPolygon> output;
    (void)::boost::geometry::intersection(leftPolygon, rightPolygon, output);
    return (!output.empty());
  } catch (...) {
    std::cerr << "Error while checking overlap between lanes " << leftLane.id
              << " and " << rightLane.id << "\n";
    return false;
  }
}
}  // namespace geometry
}  // namespace opendrive
