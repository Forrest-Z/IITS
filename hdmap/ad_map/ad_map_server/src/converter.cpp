#include "converter.h"

namespace map_server {
// convert ID: int to string
std::string convertID(const int& id) { return std::to_string(id); }

int convertID(const std::string& id) { return std::stoi(id); }

ENUPoint convertPoint(const ::common::math::geom::Point3d& point) {
  return createENUPoint(point.x, point.y, point.z);
}

// convert lane type: lane:LaneType to laneSegment Type
lane::LaneSegment::Type convertLaneType(
    ::ad::map::lane::LaneType
        type) {  // WARNING: not convertable for some types
  switch (type) {
    case ::ad::map::lane::LaneType::NORMAL:
      return lane::LaneSegment::Type::LaneSegment_Type_HIGHWAY_DRIVING;
    case ::ad::map::lane::LaneType::SHOULDER:
      return lane::LaneSegment::Type::LaneSegment_Type_SHOULDER;
    case ::ad::map::lane::LaneType::EMERGENCY:
      return lane::LaneSegment::Type::LaneSegment_Type_EMERGENCY_LANE;
    default:
      return lane::LaneSegment::Type::LaneSegment_Type_UNDEFINED;
  }
}

// convert boundary:
lane::LaneBoundary convertEdge(const ::ad::map::point::Geometry& edge) {
  // const std::vector<Point3<T>>& points
  lane::LaneBoundary tlaneBoundary;
  for (size_t i = 0; i < edge.ecefEdge.size(); i++) {
    auto tENUpoint = toENU(edge.ecefEdge[i]);
    ::common::math::geom::Vec3<double> pos3 =
        ::common::math::geom::Vec3<double>(tENUpoint.x, tENUpoint.y,
                                           tENUpoint.z);
    tlaneBoundary.polyline.append(pos3);
  }

  tlaneBoundary.polyline_type;  // TODO!!!
  return tlaneBoundary;
}

// convert contact lanes
void convertContactLanes(const ::ad::map::lane::ContactLaneList& contactLanes,
                         std::vector<std::string>& predecessor_ids,
                         std::vector<std::string>& successor_ids,
                         std::vector<std::string>& left_neighbor_ids,
                         std::vector<std::string>& right_neighbor_ids) {
  for (size_t i = 0; i < contactLanes.size(); i++) {
    ::ad::map::lane::LaneId tlaneID = contactLanes[i].toLane;
    ::ad::map::lane::ContactLocation contactLocation =
        contactLanes[i].location;  // left, right, predecessor, successor...
    auto contactTypes =
        contactLanes[i].types;  // free, lane_change, continuation...
    if (contactLocation == ::ad::map::lane::ContactLocation::LEFT) {
      left_neighbor_ids.push_back(convertID(tlaneID));
    }
    if (contactLocation == ::ad::map::lane::ContactLocation::RIGHT) {
      right_neighbor_ids.push_back(convertID(tlaneID));
    }
    if (contactLocation == ::ad::map::lane::ContactLocation::SUCCESSOR) {
      successor_ids.push_back(convertID(tlaneID));
    }
    if (contactLocation == ::ad::map::lane::ContactLocation::PREDECESSOR) {
      predecessor_ids.push_back(convertID(tlaneID));
    }
  }
}

::common::math::geom::SimplePolygon2d ConvertLaneSegmentToPolygon(
    const std::shared_ptr<map_server::lane::LaneSegment> lane_segment) {
  ::common::math::geom::SimplePolygon2d polygon;
  auto point_size = lane_segment->left_boundary.polyline.points().size() +
                    +lane_segment->right_boundary.polyline.size() + 1;
  polygon.mutable_points()->reserve(point_size);
  for (const auto& point : lane_segment->left_boundary.polyline.points()) {
    polygon.mutable_points()->emplace_back(point.ToPoint2().x,
                                           point.ToPoint2().y);
  }
  // TODO(yu zhang): fix later
  for (int i = lane_segment->right_boundary.polyline.size() - 1; i >= 0; --i) {
    polygon.mutable_points()->emplace_back(
        lane_segment->right_boundary.polyline.points()[i].x,
        lane_segment->right_boundary.polyline.points()[i].y);
  }
  CHECK_GE_WITH_MSG(polygon.points().size(), 4,
                    "Invalid lane segment. Invalid lane graph map.",
                    polygon);  // NOLINT
  polygon.mutable_points()->emplace_back(polygon.points().at(0));
  const auto first_last_difference =
      polygon.points()[polygon.points().size() - 1] - polygon.points()[0];
  return polygon;
}

void convertSpeedLimits(
    const ::ad::map::restriction::SpeedLimitList& speedLimits,
    double& speed_limit_min_mps, double& speed_limit_max_mps) {
  if (speedLimits.size() > 0) {
    ::ad::map::restriction::SpeedLimit tspeedLimit = speedLimits[0];
    speed_limit_min_mps = 0;
    speed_limit_max_mps = double(tspeedLimit.speedLimit);
  }  //************************TODO: set null case
}

lane::CenterPolyline convertCenterPolyline(
    const lane::LaneBoundary& leftBoundary,
    const lane::LaneBoundary& rightBoundary) {
  lane::CenterPolyline tCenterLine;
  // for tCenterLine.points;
  ::common::math::geom::Point3d last_direct;
  ::common::math::geom::Point3d new_direct;
  lane::CenterPolylinePoint last_tpoint;

  for (size_t i = 0; i < leftBoundary.polyline.size(); i++) {
    lane::CenterPolylinePoint tpoint;
    //
    tpoint.pt = (leftBoundary.polyline[i] + rightBoundary.polyline[i]) / 2.0;
    tpoint.left_width_m = (leftBoundary.polyline[i] - tpoint.pt).Norm();
    tpoint.right_width_m = (tpoint.pt - rightBoundary.polyline[i]).Norm();
    if (i == 0) {
      tpoint.accumulated_s_m = 0;
      tCenterLine.points.push_back(tpoint);
      last_tpoint = tpoint;

    } else if (i == 1) {  // second point , don't be urgent to push_back it.
      new_direct = tpoint.pt - last_tpoint.pt;
      tpoint.accumulated_s_m =
          tCenterLine.points.back().accumulated_s_m + new_direct.Norm();
      last_direct = new_direct;
      last_tpoint = tpoint;
      // std::cout << " new_direct: " << new_direct.x << " , " << new_direct.y
      //           << " ,"
      //           << " , " << new_direct.z << std::endl;
    } else {
      new_direct = tpoint.pt - last_tpoint.pt;
      if (::common::math::geom::Point2d(new_direct.x, new_direct.y)
              .DotProduct(::common::math::geom::Point2d(last_direct.x,
                                                        last_direct.y)) <=
          0) {  // heading is invalid, replace last_point with tpoint.
        new_direct = tpoint.pt - tCenterLine.points.back().pt;
        // std::cout << " liwenlin new_direct: " << new_direct.x << " , "
        //           << new_direct.y << " ," << last_direct.x << " , "
        //           << last_direct.y << std::endl;
      } else {  // heading is valid , pick the last_point into the stack
        tCenterLine.points.push_back(last_tpoint);
      }
      tpoint.accumulated_s_m =
          tCenterLine.points.back().accumulated_s_m + new_direct.Norm();
      last_direct = new_direct;
      last_tpoint = tpoint;
    }
    // std::cout << " sege_dis: " << new_direct.Norm()
    //           << " accumulates: " <<
    //           tCenterLine.points.back().accumulated_s_m
    //           << std::endl;
  }
  if (!tCenterLine.points.empty()) {
    tCenterLine.points.push_back(last_tpoint);
  }
  // std::cout << " liwenlin centerline size: " << tCenterLine.points.size()
  //           << " lenth" << tCenterLine.points.back().accumulated_s_m
  //           << " left boundary size: " << leftBoundary.polyline.size()
  //           << std::endl;

  return tCenterLine;
}

}  // namespace map_server