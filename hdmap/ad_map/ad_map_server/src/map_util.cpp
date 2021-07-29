#include "map_util.h"

void MapUtility::initialize(std::string configFileName) {
  access::init(configFileName);
  std::cout << "map initialized!" << std::endl;
}

point::ParaPoint MapUtility::ENU2PARA(ENUPoint pos) {
  // auto tempLaneId = lane::uniqueLaneId(toGeo(pos));
  auto matches =
      match::AdMapMatching::findLanes(toGeo(pos), physics::Distance(1.0));

  if (matches.size() <= 0) {
    return point::ParaPoint();
  }

  // sorted by match distance
  auto point = matches[0];
  return point.lanePoint.paraPoint;
}

point::ParaPoint MapUtility::ENU2PARA(ENUPoint pos, lane::LaneId tempLaneId) {
  match::MapMatchedPosition mmpos_end;
  bool flag = lane::findNearestPointOnLane(lane::getLane(tempLaneId),
                                           point::toECEF(pos), mmpos_end);
  if (!flag) {
    return point::ParaPoint();
  }
  point::ParaPoint para = mmpos_end.lanePoint.paraPoint;
  return para;
}

void MapUtility::Routing(ENUPoint startPoint, ENUPoint endPoint,
                         std::vector<ENUPoint> &route_points,
                         std::vector<uint64_t> &route_laneIDs) {
  route::FullRoute routeResult =
      route::planning::planRoute(ENU2PARA(startPoint), ENU2PARA(endPoint),
                                 route::RouteCreationMode::Undefined);
  route::RoadSegmentList roads = routeResult.roadSegments;

  route_points.clear();
  route_laneIDs.clear();

  physics::Distance deltDist = 0.01;
  // std::vector<ECEFPoint> waypoints;
  for (size_t i = 0; i < roads.size(); i++) {
    route::LaneSegmentList tlanes = roads[i].drivableLaneSegments;
    for (size_t j = 0; j < tlanes.size(); j++) {
      route::LaneSegment tlane = tlanes[j];
      lane::LaneId tlaneID = tlane.laneInterval.laneId;
      lane::Lane tlane2 = lane::getLane(tlaneID);
      if (tlane2.type == lane::LaneType::SHOULDER ||
          tlane2.type == lane::LaneType::PEDESTRIAN ||
          tlane2.type == lane::LaneType::BIKE) {
        continue;
      }
      auto tlen = tlane2.length;
      if ((double)tlen < 0.0001) {
        std::cout << "#############tlen error" << std::endl;
        continue;
      }
      physics::Distance deltPara = deltDist / tlen;
      // std::cout<<"length: "<<tlen<<std::endl;
      // physics::Distance deltPara = 0.05;
      auto tstart = tlane.laneInterval.start;
      auto tend = tlane.laneInterval.end;
      auto tPara = tstart;
      if (tstart < tend) {
        // std::cout<<"test "<<tlaneID<<" "<<tstart<<" "<<tend<<std::endl;
        while (tPara <= tend) {
          auto tParaPoint = point::createParaPoint(tlaneID, tPara);
          auto tENUPoint = lane::getENULanePoint(tParaPoint, 0.5);
          // if((int)tlaneID == endLaneId)
          route_points.push_back(tENUPoint);
          route_laneIDs.push_back(tlaneID);
          tPara = tPara + deltPara;
        }
      } else {
        // std::cout<<"test "<<tlaneID<<" "<<tstart<<" "<<tend<<std::endl;
        while (tPara >= tend) {
          auto tParaPoint = point::createParaPoint(tlaneID, tPara);
          auto tENUPoint = lane::getENULanePoint(tParaPoint, 0.5);
          route_points.push_back(tENUPoint);
          route_laneIDs.push_back(tlaneID);
          tPara = tPara - deltPara;
        }
      }
    }
  }
}

uint64_t MapUtility::findLaneID(ENUPoint pos) {
  // return lane::uniqueLaneId(toGeo(pos));
  // static MapMatchedPositionConfidenceList ;

  auto matches =
      match::AdMapMatching::findLanes(toGeo(pos), physics::Distance(1.0));
  if (matches.size() <= 0) {
    return -1;
  }

  // sorted by match distance
  auto point = matches[0];
  return point.lanePoint.paraPoint.laneId;
}

void MapUtility::findLeftLanePosition(ENUPoint pos, bool &flag,
                                      ENUPoint &leftPoint) {
  flag = false;
  lane::LaneId requestLaneId = findLaneID(pos);
  if (requestLaneId == lane::LaneId(0)) {
    throw std::runtime_error(
        "find no laneID in position: " + std::to_string(pos.x) + " " +
        std::to_string(pos.y) + " " + std::to_string(pos.y));
  }
  lane::Lane requestLane = lane::getLane(requestLaneId);

  match::MapMatchedPosition mmpos;
  lane::findNearestPointOnLane(requestLane, point::toECEF(toGeo(pos)), mmpos);
  match::LanePoint tlanePoint = mmpos.lanePoint;

  lane::ContactLaneList contactLanes = requestLane.contactLanes;
  for (size_t i = 0; i < contactLanes.size(); i++) {
    auto tlaneID = contactLanes[i].toLane;
    lane::ContactLocation contactLocation =
        contactLanes[i].location;  // left, right, predecessor, successor...
    auto contactTypes =
        contactLanes[i].types;  // free, lane_change, continuation...
    if (contactLocation == lane::ContactLocation::LEFT) {
      if (contactTypes[0] == lane::ContactType::LANE_CHANGE) {
        ParaPoint tparaPoint_left = mmpos.lanePoint.paraPoint;
        tparaPoint_left.laneId = tlaneID;
        leftPoint = lane::getENULanePoint(tparaPoint_left, 0.5);
        flag = true;
      }
      break;
    }
  }
}

void MapUtility::findRightLanePosition(ENUPoint pos, bool &flag,
                                       ENUPoint &rightPoint) {
  flag = false;
  lane::LaneId requestLaneId = findLaneID(pos);
  if (requestLaneId == lane::LaneId(0)) {
    throw std::runtime_error(
        "find no laneID in position: " + std::to_string(pos.x) + " " +
        std::to_string(pos.y) + " " + std::to_string(pos.z));
  }
  lane::Lane requestLane = lane::getLane(requestLaneId);

  match::MapMatchedPosition mmpos;
  lane::findNearestPointOnLane(requestLane, point::toECEF(toGeo(pos)), mmpos);
  match::LanePoint tlanePoint = mmpos.lanePoint;

  lane::ContactLaneList contactLanes = requestLane.contactLanes;
  for (size_t i = 0; i < contactLanes.size(); i++) {
    auto tlaneID = contactLanes[i].toLane;
    lane::ContactLocation contactLocation =
        contactLanes[i].location;  // left, right, predecessor, successor...
    auto contactTypes =
        contactLanes[i].types;  // free, lane_change, continuation...
    if (contactLocation == lane::ContactLocation::RIGHT) {
      if (contactTypes[0] == lane::ContactType::LANE_CHANGE) {
        ParaPoint tparaPoint_right = mmpos.lanePoint.paraPoint;
        tparaPoint_right.laneId = tlaneID;
        rightPoint = lane::getENULanePoint(tparaPoint_right, 0.5);
        flag = true;
      }
      break;
    }
  }
}

double MapUtility::getSlop(ENUPoint pos) {
  double delt = 0.01;
  point::ParaPoint tparaPoint = ENU2PARA(pos);
  int tlaneID = tparaPoint.laneId;
  double tpara = tparaPoint.parametricOffset;
  double slop;
  if (tpara <= 1.0 - delt) {
    point::ParaPoint tparaPoint2 =
        point::createParaPoint(tlaneID, tpara + delt);
    ENUPoint pos2 = lane::getENULanePoint(tparaPoint2, 0.5);
    slop = (pos2.z - pos.z) / sqrt((pos2.x - pos.x) * (pos2.x - pos.x) +
                                   (pos2.y - pos.y) * (pos2.y - pos.y));
  } else {
    point::ParaPoint tparaPoint2 =
        point::createParaPoint(tlaneID, tpara - delt);
    ENUPoint pos2 = lane::getENULanePoint(tparaPoint2, 0.5);
    slop = (pos2.z - pos.z) / sqrt((pos.x - pos2.x) * (pos.x - pos2.x) +
                                   (pos.y - pos.y) * (pos.y - pos2.y));
  }

  return slop;
}

physics::Distance MapUtility::distance2D(ECEFPoint point, ECEFPoint other) {
  ENUPoint tpoint = toENU(point);
  ENUPoint tother = toENU(other);
  // return vectorLength(vectorSub(point, other));
  return sqrt(((double)tpoint.x - (double)tother.x) *
                  ((double)tpoint.x - (double)tother.x) +
              ((double)tpoint.y - (double)tother.y) *
                  ((double)tpoint.y - (double)tother.y));
}

/**
 * @brief Finds point on geometry nearest to given point.
 * @param[in] pt Point of interest.
 * @returns Parametric point on geometry nearest to the pt.
 *          Can be invalid (if pt is Invalid(), geometry is empty etc.).
 */
template <typename PointType>
physics::ParametricValue MapUtility::findNearestPointOnEdge2D(
    std::vector<PointType> const &edge, physics::Distance const &edgeLength,
    const PointType &pt) {
  if (isValid(pt)) {
    if (edge.size() == 0) {
      return physics::ParametricValue();
    } else if ((edge.size() == 1) || (edgeLength == physics::Distance(0.))) {
      return physics::ParametricValue(0);
    } else {
      physics::ParametricValue t_one =
          findNearestPointOnSegment2D(pt, edge[0], edge[1]);
      PointType pt_nearest = vectorInterpolate(edge[0], edge[1], t_one);
      physics::Distance d_nearest = distance2D(pt, pt_nearest);
      physics::Distance offset_nearest = distance2D(pt_nearest, edge[0]);
      physics::Distance running_offset = physics::Distance(0);
      for (size_t i = 1; i + 1 < edge.size(); i++) {
        physics::ParametricValue t =
            findNearestPointOnSegment2D(pt, edge[i], edge[i + 1]);
        PointType pt_candidate = vectorInterpolate(edge[i], edge[i + 1], t);
        physics::Distance d = distance2D(pt_candidate, pt);
        running_offset += distance2D(edge[i - 1], edge[i]);
        if (d < d_nearest) {
          pt_nearest = pt_candidate;
          d_nearest = d;
          offset_nearest = running_offset + distance2D(pt_nearest, edge[i]);
        }
      }
      return physics::ParametricValue(offset_nearest / edgeLength);
    }
  } else {
    return physics::ParametricValue();
  }
}

/**
 * @brief Find point nearest to the line formed by two points.
 *
 * @param[in] a point to search for
 * @param[in] pt0 First point of the line.
 * @param[in] pt1 Second point of the line.
 * @returns Value of t;  nearest point to a can be calculated as
 * (1-t)*pt0+t*pt1.
 */
template <typename PointType>
physics::RatioValue MapUtility::findNearestPointOnEdge2D(PointType a,
                                                         PointType pt0,
                                                         PointType pt1) {
  ENUPoint a_ENU = point::toENU(a);
  ENUPoint pt0_ENU = point::toENU(pt0);
  ENUPoint pt1_ENU = point::toENU(pt1);
  a_ENU.z = 0;
  pt0_ENU.z = 0;
  pt1_ENU.z = 0;

  ENUPoint line = pt1_ENU - pt0_ENU;
  ENUPoint pt02a = a_ENU - pt0_ENU;
  auto const divisor = vectorDotProduct(line, line);
  if (physics::Distance(divisor) > physics::Distance(0)) {
    auto const dividend = vectorDotProduct(pt02a, line);
    auto result = dividend / divisor;
    return physics::RatioValue(result);
  } else {
    return physics::RatioValue(0.5);
  }
}

template <typename PointType>
physics::ParametricValue MapUtility::findNearestPointOnSegment2D(
    PointType const &a, const PointType &pt0, const PointType &pt1) {
  auto const t = findNearestPointOnEdge2D(a, pt0, pt1);
  if (t < physics::RatioValue(0.)) {
    return physics::ParametricValue(0.);
  } else if (t > physics::RatioValue(1.)) {
    return physics::ParametricValue(1.);
  } else {
    return physics::ParametricValue(static_cast<double>(t));
  }
}

/**
 * @brief Calculate the length of an edge
 * @param[in] edge The input edge to operate on.
 * @return The length of the edge
 */
template <typename PointType>
physics::Distance MapUtility::calculateEdgeLength2D(
    std::vector<PointType> const &edge) {
  physics::Distance length(0.);
  for (auto i = 1u; i < edge.size(); ++i) {
    length += distance2D(edge[i - 1u], edge[i]);
  }
  return length;
}

template <typename PointType>
physics::ParametricValue MapUtility::findNearestPointOnEdge2D(
    std::vector<PointType> const &edge, PointType const &pt) {
  return findNearestPointOnEdge2D(edge, calculateEdgeLength2D(edge), pt);
}

bool MapUtility::findNearestPointOnLane2D(lane::Lane const &lane,
                                          point::ECEFPoint const &pt,
                                          match::MapMatchedPosition &mmpos) {
  auto const longTLeft = findNearestPointOnEdge2D(lane.edgeLeft.ecefEdge, pt);
  // std::cout<<"test: longTLeft: "<<longTLeft<<"
  // "<<longTLeft.isValid()<<std::endl;
  if (longTLeft.isValid()) {
    auto const longTRight =
        findNearestPointOnEdge2D(lane.edgeRight.ecefEdge, pt);
    // std::cout<<"test: longTRight: "<<longTRight<<"
    // "<<longTRight.isValid()<<std::endl;
    if (longTRight.isValid()) {
      point::ECEFPoint const pt_left =
          point::getParametricPoint(lane.edgeLeft, longTLeft);
      point::ECEFPoint const pt_right =
          point::getParametricPoint(lane.edgeRight, longTRight);

      mmpos.lanePoint.paraPoint.laneId = lane.id;
      mmpos.lanePoint.lateralT =
          findNearestPointOnEdge2D(pt, pt_left, pt_right);
      physics::ParametricValue nearestT;
      if (mmpos.lanePoint.lateralT < physics::RatioValue(0.)) {
        nearestT = physics::ParametricValue(0.);
        mmpos.type = match::MapMatchedPositionType::LANE_LEFT;
        mmpos.probability = std::max(
            physics::Probability(0.1),
            physics::Probability(
                0.5 + static_cast<double>(mmpos.lanePoint.lateralT) / 10.));
      } else if (mmpos.lanePoint.lateralT > physics::RatioValue(1.)) {
        nearestT = physics::ParametricValue(1.);
        mmpos.type = match::MapMatchedPositionType::LANE_RIGHT;
        mmpos.probability = std::max(
            physics::Probability(0.1),
            physics::Probability(
                0.5 -
                (static_cast<double>(mmpos.lanePoint.lateralT) - 1.) / 10.));
      } else {
        nearestT = physics::ParametricValue(
            static_cast<double>(mmpos.lanePoint.lateralT));
        mmpos.type = match::MapMatchedPositionType::LANE_IN;
        mmpos.probability =
            physics::Probability(1.) -
            std::min(physics::Probability(0.5),
                     physics::Probability(fabs(
                         0.5 - static_cast<double>(mmpos.lanePoint.lateralT))));
      }
      mmpos.matchedPoint =
          point::vectorInterpolate(pt_left, pt_right, nearestT);
      mmpos.lanePoint.paraPoint.parametricOffset =
          nearestT * longTLeft +
          (physics::ParametricValue(1.) - nearestT) * longTRight;
      mmpos.lanePoint.laneLength = lane.length;
      mmpos.lanePoint.laneWidth = distance2D(pt_left, pt_right);
      mmpos.queryPoint = pt;
      mmpos.matchedPointDistance =
          distance2D(mmpos.matchedPoint, mmpos.queryPoint);
      // std::cout<<"mmpos true"<<std::endl;
      return true;
    }
  }
  return false;
}

std::vector<lane::Lane::ConstPtr> MapUtility::getRelevantLanesInputChecked2D(
    point::ECEFPoint const &ecefPoint, physics::Distance const &distance) {
  // std::cout<<"test: getRelevantLanesInputChecked2D"<<std::endl;
  std::vector<lane::Lane::ConstPtr> relevantLanes;
  point::BoundingSphere matchingSphere;
  matchingSphere.center = ecefPoint;
  matchingSphere.radius = distance;
  int count = 0;
  for (auto laneId : access::getStore().getLanes()) {
    auto lane = access::getStore().getLanePtr(laneId);

    if (lane) {
      // if(count<15){
      //   std::cout<<count<<" "<<lane->id<<" "<<lane->boundingSphere<<" "
      //   <<matchingSphere<<" "<<toENU(lane->boundingSphere.center)<<"
      //   "<<toENU(matchingSphere.center)<<" "
      //   <<distance2D(lane->boundingSphere,matchingSphere)<<" "<<std::endl;
      // }
      if (isNear2D(*lane, matchingSphere)) {
        relevantLanes.push_back(lane);
      }
    }
    count++;
  }

  return relevantLanes;
}

physics::Distance MapUtility::distance2D(BoundingSphere const &left,
                                         BoundingSphere const &right) {
  // std::cout<<"test: distance2D "<<left.center<<" "<<left.radius<<"
  // "<<right.center<<" "<<right.radius<<std::endl;
  physics::Distance const distanceCenter =
      distance2D(left.center, right.center);
  // std::cout<<distanceCenter<<std::endl;

  return std::max(physics::Distance(0u),
                  distanceCenter - left.radius - right.radius);
}

match::MapMatchedPositionConfidenceList MapUtility::findLanesInputChecked2D(
    point::ECEFPoint const &ecefPoint, physics::Distance const &distance) {
  return findLanesInputChecked2D(
      getRelevantLanesInputChecked2D(ecefPoint, distance), ecefPoint, distance);
}

match::MapMatchedPositionConfidenceList MapUtility::findLanes2D(
    point::GeoPoint const &geoPoint, physics::Distance const &distance) {
  return findLanesInputChecked2D(point::toECEF(geoPoint), distance);
}

bool MapUtility::isNear2D(lane::Lane const &lane,
                          point::BoundingSphere const &boundingSphere) {
  return distance2D(lane.boundingSphere, boundingSphere) ==
         physics::Distance(0.);
}

match::MapMatchedPositionConfidenceList MapUtility::findLanesInputChecked2D(
    std::vector<lane::Lane::ConstPtr> const &relevantLanes,
    point::ECEFPoint const &ecefPoint, physics::Distance const &distance) {
  // std::cout<<"test: findLanesInputChecked2D 2"<<std::endl;
  match::MapMatchedPositionConfidenceList mapMatchingResults;
  physics::Probability probabilitySum(0.);
  // std::cout<<"relevantLanes: "<<relevantLanes.size()<<std::endl;
  for (auto lane : relevantLanes) {
    // std::cout<<"test: laneID: "<<lane->id<<std::endl;
    match::MapMatchedPosition mmpt;
    if (findNearestPointOnLane2D(*lane, ecefPoint, mmpt)) {
      if (mmpt.matchedPointDistance <= distance) {
        mapMatchingResults.push_back(mmpt);
        probabilitySum += mmpt.probability;
      }
    }
  }

  // std::cout<<"test: mapMatchingResults:
  // "<<mapMatchingResults.size()<<std::endl; normalize result probabilities
  if (probabilitySum > physics::Probability(0.01)) {
    for (auto &mmpt : mapMatchingResults) {
      mmpt.probability = mmpt.probability / static_cast<double>(probabilitySum);
    }
  }

  // sort the final results
  std::sort(std::begin(mapMatchingResults), std::end(mapMatchingResults),
            [](match::MapMatchedPosition const &left,
               match::MapMatchedPosition const &right) {
              return left.probability > right.probability;
            });
  return mapMatchingResults;
}

double MapUtility::getZ(double x, double y, unsigned int tlaneID) {
  // match::AdMapMatching mapMatching;
  // auto mapMatchingResult
  //     = mapMatching.getMapMatchedPositions(geoPoint, physics::Distance(0.1),
  //     physics::Probability(0.5));

  //******************************************************find the para
  lane::Lane requestLane = lane::getLane(tlaneID);

  match::MapMatchedPosition mmpos;
  findNearestPointOnLane2D(
      requestLane, point::toECEF(toGeo(createENUPoint(x, y, 0.0))), mmpos);

  auto tPoint_ECEF = mmpos.matchedPoint;
  auto tPoint_ENU = toENU(tPoint_ECEF);

  //******************************************************get the z
  return tPoint_ENU.z;
}

double MapUtility::getZ(double x, double y) {
  auto mapMatchingResult = findLanes2D(
      toGeo(point::createENUPoint(x, y, (double)0.0)), physics::Distance(5.0));
  auto matchedPoint = toENU(mapMatchingResult[0].matchedPoint);
  return matchedPoint.z;
}

void MapUtility::getZ(double x, double y, double &z, unsigned int &laneID) {
  auto mapMatchingResult = findLanes2D(
      toGeo(point::createENUPoint(x, y, (double)0.0)), physics::Distance(5.0));
  if (mapMatchingResult.size() > 0) {
    laneID = mapMatchingResult[0].lanePoint.paraPoint.laneId;
    auto matchedPoint = toENU(mapMatchingResult[0].matchedPoint);
    z = matchedPoint.z;
  } else {
    laneID = 0;
    z = 0.0;
  }
}

void MapUtility::getAllLanes(std::vector<LaneEdges> &laneEdges) {
  for (auto laneId : lane::getLanes()) {
    LaneEdges tempLaneEdge;
    tempLaneEdge.laneID = laneId;

    lane::Lane lane = lane::getLane(laneId);

    tempLaneEdge.laneType = lane.type;
    if (lane.type == lane::LaneType::SHOULDER ||
        lane.type == lane::LaneType::PEDESTRIAN ||
        lane.type == lane::LaneType::BIKE) {
      laneEdges.push_back(tempLaneEdge);
      continue;
    }

    auto leftEdge = lane.edgeLeft.ecefEdge;
    auto rightEdge = lane.edgeRight.ecefEdge;
    // convert edge
    for (size_t i = 0; i < leftEdge.size(); i++) {
      tempLaneEdge.leftEdge.push_back(toENU(leftEdge[i]));
    }
    for (size_t i = 0; i < rightEdge.size(); i++) {
      tempLaneEdge.rightEdge.push_back(toENU(rightEdge[i]));
    }

    tempLaneEdge.leftEdgeType = 0;
    tempLaneEdge.rightEdgeType = 0;

    lane::ContactLaneList contactLanes = lane.contactLanes;
    for (size_t i = 0; i < contactLanes.size(); i++) {
      auto tlaneID = contactLanes[i].toLane;
      lane::ContactLocation contactLocation =
          contactLanes[i].location;  // left, right, predecessor, successor...
      auto contactTypes =
          contactLanes[i].types;  // free, lane_change, continuation...
      if (contactLocation == lane::ContactLocation::RIGHT) {
        tempLaneEdge.rightEdgeType = 1;
      }
      if (contactLocation == lane::ContactLocation::LEFT) {
        tempLaneEdge.leftEdgeType = 1;
      }
    }

    laneEdges.push_back(tempLaneEdge);
  }
}

void MapUtility::getDistance(const ENUPoint &startPoint,
                             const ENUPoint &endPoint, double *distance) {
  bool dealOverlap = true;
  auto startParaPoint = ENU2PARA(startPoint);
  auto endParaPoint = ENU2PARA(endPoint);
  *distance = 0;

  route::FullRoute routeResult = route::planning::planRoute(
      startParaPoint, endParaPoint, route::RouteCreationMode::Undefined);

  route::RoadSegmentList roads = routeResult.roadSegments;

  // vector<ECEFPoint> waypoints;
  route::LaneSegmentList tlanes_old;
  for (size_t i = 0; i < roads.size(); i++) {
    route::LaneSegmentList tlanes = roads[i].drivableLaneSegments;

    route::LaneSegment tlane = tlanes[0];
    lane::LaneId tlaneID = tlane.laneInterval.laneId;
    lane::Lane tlane2 = lane::getLane(tlaneID);

    if (tlane2.type == lane::LaneType::SHOULDER ||
        tlane2.type == lane::LaneType::PEDESTRIAN ||
        tlane2.type == lane::LaneType::BIKE) {
      continue;
    }
    if (!dealOverlap || i == 0) {
      double tstartPara = tlane.laneInterval.start;
      double tendPara = tlane.laneInterval.end;
      double tlength = tlane2.length * (tendPara - tstartPara);
      *distance = *distance + tlength;
    } else {
      double priorPoint_para = tlanes_old[0].laneInterval.end;
      // ENUPoint tPoint_ENU = waypoints_ENU[i-1];
      auto tParaPoint_prior = point::createParaPoint(
          tlanes_old[0].laneInterval.laneId, priorPoint_para);
      auto tENUPoint_prior = lane::getENULanePoint(tParaPoint_prior, 0.5);
      auto tParaPoint =
          ENU2PARA(tENUPoint_prior, tlanes[0].laneInterval.laneId);
      // cout<<i<<" "<<(double)tParaPoint.parametricOffset<<endl;
      if ((double)tParaPoint.parametricOffset > 0.0) {
        double tpara_start = (double)tParaPoint.parametricOffset;
        double tlength =
            tlane2.length * ((double)tlane.laneInterval.end - tpara_start);
        *distance = *distance + tlength;
      }
    }
    tlanes_old = tlanes;
  }
}