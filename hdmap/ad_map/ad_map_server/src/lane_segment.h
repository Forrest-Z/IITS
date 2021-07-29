//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//

#ifndef HDMAP_AD_MAP_AD_MAP_SERVER_LANE_SEGMENT_H_
#define HDMAP_AD_MAP_AD_MAP_SERVER_LANE_SEGMENT_H_

#include "ad/map/access/Factory.hpp"
#include "ad/map/access/Operation.hpp"
#include "ad/map/config/MapConfigFileHandler.hpp"
#include "ad/map/lane/Lane.hpp"
#include "ad/map/lane/LaneOperation.hpp"
#include "ad/map/lane/LaneType.hpp"
#include "ad/map/match/AdMapMatching.hpp"
#include "ad/map/match/Types.hpp"
#include "ad/map/point/Operation.hpp"
#include "ad/map/route/Planning.hpp"
#include "ad/map/route/RouteOperation.hpp"
#include "center_polyline.h"
#include "lane_boundary.h"
#include "lane_segment.h"
#include "map_util.h"
#include "opendrive/OpenDrive.hpp"

using namespace ::ad;
using namespace ::ad::map;
using namespace ::ad::map::point;

namespace map_server {
namespace lane {

class LaneSegment {
 public:
  enum class LaneTurn : uint8_t {
    LaneSegment_LaneTurn_LANE_TURN_UNDEFINED = 0,
    LaneSegment_LaneTurn_LEFT_MERGE = 1,
    LaneSegment_LaneTurn_LEFT_SPLIT = 2,
    LaneSegment_LaneTurn_LEFT_TURN = 3,
    LaneSegment_LaneTurn_RIGHT_MERGE = 4,
    LaneSegment_LaneTurn_RIGHT_SPLIT = 5,
    LaneSegment_LaneTurn_RIGHT_TURN = 6,
    LaneSegment_LaneTurn_STRAIGHT = 7,
    LaneSegment_LaneTurn_U_TURN = 8,
  };

  enum class Type : uint8_t {
    LaneSegment_Type_UNDEFINED = 0,
    LaneSegment_Type_CITY_DRIVING = 1,
    LaneSegment_Type_HIGHWAY_DRIVING = 2,
    LaneSegment_Type_EMERGENCY_LANE = 3,
    LaneSegment_Type_BIKING = 4,
    LaneSegment_Type_SHOULDER = 5,
    LaneSegment_Type_PARKING = 6,
    LaneSegment_Type_PAVEMENT = 7,
    LaneSegment_Type_MAX_LANE_TYPE = 8,
  };

 public:
  std::string id;
  ::ad::map::lane::LaneType type_ad;
  Type type;
  LaneTurn lane_turn;

  // The left/right boundary are the lane marker boundary.
  // For the detail refer to the design document.
  ::ad::map::point::Geometry edgeLeft_ad;
  ::ad::map::point::Geometry edgeRight_ad;
  LaneBoundary left_boundary;
  LaneBoundary right_boundary;

  /*!
   * List of contacting lanes
   */
  ::ad::map::lane::ContactLaneList contactLanes_ad;
  // The predecessor, successor, left neighbor, right neighbor ids.
  std::vector<std::string> predecessor_ids;
  std::vector<std::string> successor_ids;
  std::vector<std::string> left_neighbor_ids;
  std::vector<std::string> right_neighbor_ids;

  // The merge and split lane ids if this lane is a merge/split lane segment.
  std::vector<std::string> merge_neighbor_ids;
  std::vector<std::string> split_neighbor_ids;

  // The speed limit range.
  ::ad::map::restriction::SpeedLimitList speedLimits;
  double speed_limit_min_mps;  // Unit in m/s TODO(yu zhang): change later
  double speed_limit_max_mps;  // Unit in m/s

  // The center polyline.
  CenterPolyline center_polyline;

  // TODO(yu zhang): currently we may have no traffic related data
  // The traffic instrument ids.
  std::vector<std::string> traffic_light_ids;
  // std::vector<std::string> traffic_sign_ids;
};

// name alias
using LaneSegmentCPtr = std::shared_ptr<const LaneSegment>;

}  // namespace lane
}  // namespace map_server

#endif  // HDMAP_AD_MAP_AD_MAP_SERVER_LANE_SEGMENT_H_