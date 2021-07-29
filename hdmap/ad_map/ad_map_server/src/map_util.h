//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//

#ifndef HDMAP_AD_MAP_AD_MAP_SERVER_MAP_UTILS_H_
#define HDMAP_AD_MAP_AD_MAP_SERVER_MAP_UTILS_H_

#include "ad/map/access/Factory.hpp"
#include "ad/map/access/Operation.hpp"
#include "ad/map/config/MapConfigFileHandler.hpp"
#include "ad/map/lane/Lane.hpp"
#include "ad/map/lane/LaneOperation.hpp"
#include "ad/map/match/AdMapMatching.hpp"
#include "ad/map/match/Types.hpp"
#include "ad/map/point/Operation.hpp"
#include "ad/map/route/Planning.hpp"
#include "ad/map/route/RouteOperation.hpp"
#include "opendrive/OpenDrive.hpp"
using namespace ::ad;
using namespace ::ad::map;
using namespace ::ad::map::point;

struct LaneEdges {
  std::vector<ENUPoint> leftEdge;
  std::vector<ENUPoint> rightEdge;
  int leftEdgeType;  // 0: solid edge; 1: dashed edge
  int rightEdgeType;
  ::ad::map::lane::LaneType laneType;
  int laneID;
};

class MapUtility {
 public:
  MapUtility() {}
  //～MapUtility(){}

  void initialize(std::string configFileName);

  void Routing(ENUPoint startPoint, ENUPoint endPoint,
               std::vector<ENUPoint> &route_points,
               std::vector<uint64_t> &route_laneIDs);

  uint64_t findLaneID(ENUPoint pos);

  void findLeftLanePosition(ENUPoint pos, bool &flag, ENUPoint &leftPoint);

  void findRightLanePosition(ENUPoint pos, bool &flag, ENUPoint &rightPoint);

  point::ParaPoint ENU2PARA(ENUPoint pos);
  point::ParaPoint ENU2PARA(ENUPoint pos, lane::LaneId tempLaneId);

  std::vector<ENUPoint> map_allPoints_ENU;

  double getSlop(ENUPoint pos);

  physics::Distance distance2D(ECEFPoint point, ECEFPoint other);

  template <typename PointType>
  physics::ParametricValue findNearestPointOnEdge2D(
      std::vector<PointType> const &edge, physics::Distance const &edgeLength,
      PointType const &pt);

  bool findNearestPointOnLane2D(::ad::map::lane::Lane const &lane,
                                point::ECEFPoint const &pt,
                                match::MapMatchedPosition &mmpos);

  template <typename PointType>
  physics::ParametricValue findNearestPointOnEdge2D(
      std::vector<PointType> const &edge, const PointType &pt);
  template <typename PointType>
  physics::Distance calculateEdgeLength2D(std::vector<PointType> const &edge);
  template <typename PointType>
  physics::RatioValue findNearestPointOnEdge2D(PointType a, PointType pt0,
                                               PointType pt1);

  template <typename PointType>
  physics::ParametricValue findNearestPointOnSegment2D(PointType const &a,
                                                       const PointType &pt0,
                                                       const PointType &pt1);
  physics::Distance distance2D(BoundingSphere const &left,
                               BoundingSphere const &right);

  bool isNear2D(::ad::map::lane::Lane const &lane,
                point::BoundingSphere const &boundingSphere);
  std::vector<::ad::map::lane::Lane::ConstPtr> getRelevantLanesInputChecked2D(
      point::ECEFPoint const &ecefPoint, physics::Distance const &distance);
  match::MapMatchedPositionConfidenceList getMapMatchedPositions2D(
      point::GeoPoint const &geoPoint, physics::Distance const &distance,
      physics::Probability const &minProbability);
  match::MapMatchedPositionConfidenceList findLanesInputChecked2D(
      point::ECEFPoint const &ecefPoint, physics::Distance const &distance);
  match::MapMatchedPositionConfidenceList findLanes2D(
      point::GeoPoint const &geoPoint, physics::Distance const &distance);
  match::MapMatchedPositionConfidenceList findLanesInputChecked2D(
      std::vector<::ad::map::lane::Lane::ConstPtr> const &relevantLanes,
      point::ECEFPoint const &ecefPoint, physics::Distance const &distance);

  double getZ(double x, double y, unsigned int tlaneID);
  double getZ(double x, double y);
  void getZ(double x, double y, double &z, unsigned int &laneID);

  void getAllLanes(std::vector<LaneEdges> &laneEdges);

  void getDistance(const ENUPoint &startPoint, const ENUPoint &endPoint,
                   double *distance);
};
#endif