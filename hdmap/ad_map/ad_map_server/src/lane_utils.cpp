#include "lane_utils.h"

#include <string>

#include "converter.h"

using namespace map_server;
namespace map_server {

std::shared_ptr<map_server::lane::LaneSegment> LaneUtils::GetLaneSegmentFromID(
    const std::string& laneID) {
  ::ad::map::lane::LaneId tlaneID = convertID(laneID);
  auto const lane = ::ad::map::access::getStore().getLanePtr(tlaneID);
  if (!bool(lane)) {
    return nullptr;
  }
  ::ad::map::lane::Lane tlane = ::ad::map::lane::getLane(tlaneID);
  auto tLaneSeg = std::make_shared<map_server::lane::LaneSegment>();
  tLaneSeg->id = laneID;
  tLaneSeg->type_ad = tlane.type;
  tLaneSeg->type = convertLaneType(tLaneSeg->type_ad);
  tLaneSeg->lane_turn;  //**************************************TODO: check this
                        // information
  tLaneSeg->edgeLeft_ad = tlane.edgeLeft;
  tLaneSeg->left_boundary = convertEdge(tLaneSeg->edgeLeft_ad);
  tLaneSeg->edgeRight_ad = tlane.edgeRight;
  tLaneSeg->right_boundary = convertEdge(tLaneSeg->edgeRight_ad);
  tLaneSeg->contactLanes_ad = tlane.contactLanes;
  convertContactLanes(tLaneSeg->contactLanes_ad, tLaneSeg->predecessor_ids,
                      tLaneSeg->successor_ids, tLaneSeg->left_neighbor_ids,
                      tLaneSeg->right_neighbor_ids);
  tLaneSeg->merge_neighbor_ids;  //**************************************TODO:
                                 // check this information
  tLaneSeg->split_neighbor_ids;  //**************************************TODO:
                                 // check this information

  // The speed limit range.
  tLaneSeg->speedLimits = tlane.speedLimits;
  convertSpeedLimits(tLaneSeg->speedLimits, tLaneSeg->speed_limit_min_mps,
                     tLaneSeg->speed_limit_max_mps);
  // The center polyline.
  tLaneSeg->center_polyline = convertCenterPolyline(
      tLaneSeg->left_boundary,
      tLaneSeg->right_boundary);  //**************************************TODO:
                                  // compute center line

  // TODO(yu zhang): currently we may have no traffic related data
  // The traffic instrument ids.
  tLaneSeg->traffic_light_ids;  //**************************************TODO:
                                // check this information
  return tLaneSeg;
}

std::vector<std::shared_ptr<map_server::lane::LaneSegment>>
LaneUtils::GetNearestLaneSegmentsFromPoint(
    const ::common::math::geom::Point3d& query_point) {
  // 3d point -> ENUPoint
  ENUPoint tpoint = convertPoint(query_point);
  // getLaneId
  auto tlaneID = findLaneID(tpoint);

  // getLaneSegment by laneID
  std::vector<std::shared_ptr<map_server::lane::LaneSegment>> tLanSegments;
  tLanSegments.push_back(GetLaneSegmentFromID(convertID(tlaneID)));
  return tLanSegments;
}

std::vector<std::shared_ptr<map_server::lane::LaneSegment>>
LaneUtils::GetNearestLaneSegmentsFromPoint(
    const ::common::math::geom::Point2d& query_point) {
  // 2d point -> 3d point
  double z;
  unsigned int tlaneID;
  ::common::utils::base::TimerElapsed tic;
  getZ(query_point.x, query_point.y, z, tlaneID);
  const int elapsed_time_ms = static_cast<int>(tic.TocElapsedMs());
  LOG_INFO_STREAM("lane_utils: getZ", " time = " << elapsed_time_ms << " ms");
  // getLaneSegment by laneID
  std::vector<std::shared_ptr<map_server::lane::LaneSegment>> tLanSegments;
  tLanSegments.push_back(GetLaneSegmentFromID(convertID(tlaneID)));
  return tLanSegments;
}

std::unique_ptr<lane::CenterPolylinePoint>
LaneUtils::GetNearestCenterPolylinePoint(
    const std::string& lane_id,
    const ::common::math::geom::Point3d& query_point) {
  return GetNearestCenterPolylinePoint(lane_id, query_point.ToPoint2());
}

std::unique_ptr<lane::CenterPolylinePoint>
LaneUtils::GetNearestCenterPolylinePoint(
    const std::string& lane_id,
    const ::common::math::geom::Point2d& query_point) {
  const auto lane_segment = GetLaneSegmentFromID(lane_id);
  if (lane_segment == nullptr) {
    return nullptr;
  }
  if (lane_segment->center_polyline.points.empty()) {
    return nullptr;
  }

  const auto& first_point = lane_segment->center_polyline.points[0];
  const auto& last_point = lane_segment->center_polyline.points.back();

  if ((query_point - first_point.pt.ToPoint2()).Norm() < 1e-8) {
    return std::make_unique<lane::CenterPolylinePoint>(first_point);
  } else if ((query_point - last_point.pt.ToPoint2()).Norm() < 1e-8) {
    return std::make_unique<lane::CenterPolylinePoint>(last_point);
  }

  ::common::math::geom::SimplePolygon2d lane_polygon =
      ConvertLaneSegmentToPolygon(lane_segment);
  if (!::common::math::geom::CoveredBy(query_point, lane_polygon)) {
    return nullptr;
  }
  double min_distance;
  size_t nearest_point_index;
  if (!GetNearestPointOnCenterPolyline(lane_segment->center_polyline,
                                       query_point, &nearest_point_index,
                                       &min_distance)) {
    return nullptr;
  }

  return std::make_unique<lane::CenterPolylinePoint>(
      lane_segment->center_polyline.points[nearest_point_index]);
}

bool LaneUtils::GetNearestPointOnCenterPolyline(
    const lane::CenterPolyline& center_polyline,
    const ::common::math::geom::Point2d& query_point, size_t* point_index,
    double* min_distance_m) {
  if (!point_index) {
    return false;
  }
  if (center_polyline.points.empty()) {
    return false;
  }

  double min_distance_local = std::numeric_limits<double>::max();
  *point_index = center_polyline.points.size();

  for (size_t k = 0; k < center_polyline.points.size(); ++k) {
    const auto& polyline_point = center_polyline.points[k];
    const double cur_distance =
        polyline_point.pt.ToPoint2().Distance(query_point);
    if (cur_distance < min_distance_local) {
      min_distance_local = cur_distance;
      *point_index = k;
    }
  }
  if (*point_index == center_polyline.points.size()) {
    return false;
  }
  if (min_distance_m) {
    *min_distance_m = min_distance_local;
  }
  return true;
}

std::unique_ptr<::common::math::geom::ProjectedPoint2d>
LaneUtils::GetFrenetProjectionCenterPolyline(
    const std::string& lane_segment_id,
    const ::common::math::geom::Point3d& proj_point) {
  return GetFrenetProjectionCenterPolyline(lane_segment_id,
                                           proj_point.ToPoint2());
}

std::unique_ptr<::common::math::geom::ProjectedPoint2d>
LaneUtils::GetFrenetProjectionCenterPolyline(
    const std::string& lane_segment_id,
    const ::common::math::geom::Point2d& proj_point) {
  map_server::lane::LaneSegmentCPtr lane_segment_cptr =
      GetLaneSegmentFromID(lane_segment_id);
  if (lane_segment_cptr == nullptr) {
    LOG_WARN_STREAM("hdmap: ", "Cannot find the lane segment with given id: "
                                   << lane_segment_id);
    return nullptr;
  }
  const ::common::math::geom::Polyline3d& center_polyline =
      lane_segment_cptr->center_polyline.ToPolyline();
  const ::common::math::geom::ProjectedPoint2d& projected_pt2d =
      ::common::math::geom::ProjectPtToPolyline(proj_point,
                                                center_polyline.ToPolyline2());
  return std::make_unique<::common::math::geom::ProjectedPoint2d>(
      projected_pt2d);
}

std::unique_ptr<double> LaneUtils::GetDistance(
    const ::common::math::geom::Point2d& start_point,
    const ::common::math::geom::Point2d& end_point) {
  ::common::utils::base::TimerElapsed tic;
  ad::map::point::ENUPoint start_point_ENU = createENUPoint(
      start_point.x, start_point.y, getZ(start_point.x, start_point.y));
  const int elapsed_time_ms = static_cast<int>(tic.TocElapsedMs());
  LOG_INFO_STREAM("lane_utils: GetDistance",
                  " getz time = " << elapsed_time_ms << " ms");
  ad::map::point::ENUPoint end_point_ENU =
      createENUPoint(end_point.x, end_point.y, getZ(end_point.x, end_point.y));
  LOG_INFO_STREAM(
      "lane_utils: GetDistance",
      " getz2 time = " << static_cast<int>(tic.TocElapsedMs()) << " ms");
  double distance;
  getDistance(start_point_ENU, end_point_ENU, &distance);
  return std::make_unique<double>(distance);
}
}  // namespace map_server
