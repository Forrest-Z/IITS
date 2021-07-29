//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//

#ifndef HDMAP_AD_MAP_AD_MAP_SERVER_LANE_UTILS_H_
#define HDMAP_AD_MAP_AD_MAP_SERVER_LANE_UTILS_H_

#include <memory>

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
#include "center_polyline.h"
#include "common/utils/base/time.h"
#include "lane_segment.h"
#include "map_util.h"
#include "opendrive/OpenDrive.hpp"

using namespace ::ad;
using namespace ::ad::map;
using namespace ::ad::map::point;

namespace map_server {
class LaneUtils : public ::MapUtility {
 public:
  LaneUtils() {}
  ~LaneUtils() {}
  static LaneUtils* GetInstance() {
    static LaneUtils lane_utils;
    return &lane_utils;
  }
  std::shared_ptr<map_server::lane::LaneSegment> GetLaneSegmentFromID(
      const std::string& id);
  std::vector<std::shared_ptr<map_server::lane::LaneSegment>>
  GetNearestLaneSegmentsFromPoint(
      const ::common::math::geom::Point3d& query_point);
  std::vector<std::shared_ptr<map_server::lane::LaneSegment>>
  GetNearestLaneSegmentsFromPoint(
      const ::common::math::geom::Point2d& query_point);
  std::unique_ptr<lane::CenterPolylinePoint> GetNearestCenterPolylinePoint(
      const std::string& lane_id,
      const ::common::math::geom::Point3d& query_point);
  std::unique_ptr<lane::CenterPolylinePoint> GetNearestCenterPolylinePoint(
      const std::string& lane_id,
      const ::common::math::geom::Point2d& query_point);

  /// @brief GetFrenetProjectionCenterPolyline: get the point projection onto
  /// the lane segment center line in Frenet coordinate
  std::unique_ptr<::common::math::geom::ProjectedPoint2d>
  GetFrenetProjectionCenterPolyline(
      const std::string& lane_segment_id,
      const ::common::math::geom::Point3d& proj_point);
  std::unique_ptr<::common::math::geom::ProjectedPoint2d>
  GetFrenetProjectionCenterPolyline(
      const std::string& lane_segment_id,
      const ::common::math::geom::Point2d& proj_point);

  std::unique_ptr<double> GetDistance(
      const ::common::math::geom::Point2d& start_point,
      const ::common::math::geom::Point2d& end_point);

 private:
  bool GetNearestPointOnCenterPolyline(
      const lane::CenterPolyline& center_polyline,
      const ::common::math::geom::Point2d& query_point, size_t* point_index,
      double* min_distance_m = nullptr);
};
}  // namespace map_server
#endif
