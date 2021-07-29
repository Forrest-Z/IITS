
#include <chrono>
#include <memory>

#include "ad_to_ros_msg.h"
#include "fead_interfaces/srv/access_lane_id.hpp"
#include "fead_interfaces/srv/access_left_lane.hpp"
#include "fead_interfaces/srv/access_right_lane.hpp"
#include "fead_interfaces/srv/get_frenet_projection_center_polyline2d.hpp"
#include "fead_interfaces/srv/get_frenet_projection_center_polyline3d.hpp"
#include "fead_interfaces/srv/get_lane_segment_from_id.hpp"
#include "fead_interfaces/srv/get_map.hpp"
#include "fead_interfaces/srv/get_nearest_center_polyline_point2d.hpp"
#include "fead_interfaces/srv/get_nearest_center_polyline_point3d.hpp"
#include "fead_interfaces/srv/get_nearest_lane_segments_from_point2d.hpp"
#include "fead_interfaces/srv/get_nearest_lane_segments_from_point3d.hpp"
#include "fead_interfaces/srv/get_slop.hpp"
#include "fead_interfaces/srv/get_z.hpp"
#include "fead_interfaces/srv/routing.hpp"
#include "lane_utils.h"
#include "map_util.h"
#include "rclcpp/rclcpp.hpp"
#include "ros_to_ad_msg.h"
#include "std_msgs/msg/string.hpp"

using namespace ::ad;
using namespace ::ad::map;
using namespace ::ad::map::point;

// MapUtility maputil;
map_server::LaneUtils laneutil;

void RoutingHandler(
    const std::shared_ptr<fead_interfaces::srv::Routing::Request> request,
    std::shared_ptr<fead_interfaces::srv::Routing::Response> response) {
  auto beginPos = request->begin_pos;
  auto endPos = request->end_pos;

  ENUPoint startPos_ENU =
      ad::map::point::createENUPoint(beginPos.x, beginPos.y, beginPos.z);

  ENUPoint endPos_ENU =
      ad::map::point::createENUPoint(endPos.x, endPos.y, endPos.z);

  std::vector<ENUPoint> route_points;
  std::vector<uint64_t> route_laneIDs;

  laneutil.Routing(startPos_ENU, endPos_ENU, route_points, route_laneIDs);

  size_t tsize = route_points.size();
  response->lane_id.resize(tsize);
  response->waypoints.resize(tsize);

  for (size_t i = 0; i < route_points.size(); i++) {
    response->lane_id[i] = route_laneIDs[i];
    response->waypoints[i].x = route_points[i].x;
    response->waypoints[i].y = route_points[i].y;
    response->waypoints[i].z = route_points[i].z;
  }
}

void AccessLaneIDHandler(
    const std::shared_ptr<fead_interfaces::srv::AccessLaneID::Request> request,
    std::shared_ptr<fead_interfaces::srv::AccessLaneID::Response> response) {
  auto pos = request->waypoint;
  ENUPoint pos_ENU = createENUPoint(pos.x, pos.y, pos.z);
  response->lane_id = laneutil.findLaneID(pos_ENU);
}
void AccessLeftLaneHandler(
    const std::shared_ptr<fead_interfaces::srv::AccessLeftLane::Request>
        request,
    std::shared_ptr<fead_interfaces::srv::AccessLeftLane::Response> response) {
  auto pos = request->waypoint;
  ENUPoint pos_ENU = createENUPoint(pos.x, pos.y, pos.z);
  bool flag;
  ENUPoint pos_left;
  laneutil.findLeftLanePosition(pos_ENU, flag, pos_left);
  response->flag = flag;
  response->waypoint.x = pos_left.x;
  response->waypoint.y = pos_left.y;
  response->waypoint.z = pos_left.z;
}
void AccessRightLaneHandler(
    const std::shared_ptr<fead_interfaces::srv::AccessRightLane::Request>
        request,
    std::shared_ptr<fead_interfaces::srv::AccessRightLane::Response> response) {
  auto pos = request->waypoint;
  ENUPoint pos_ENU = createENUPoint(pos.x, pos.y, pos.z);
  bool flag;
  ENUPoint pos_right;
  laneutil.findRightLanePosition(pos_ENU, flag, pos_right);
  response->flag = flag;
  response->waypoint.x = pos_right.x;
  response->waypoint.y = pos_right.y;
  response->waypoint.z = pos_right.z;
}

void GetSlopHandler(
    const std::shared_ptr<fead_interfaces::srv::GetSlop::Request> request,
    std::shared_ptr<fead_interfaces::srv::GetSlop::Response> response) {
  auto pos = request->pos;
  ENUPoint pos_ENU = createENUPoint(pos.x, pos.y, pos.z);
  response->slop = laneutil.getSlop(pos_ENU);
}

void GetZHandler(
    const std::shared_ptr<fead_interfaces::srv::GetZ::Request> request,
    std::shared_ptr<fead_interfaces::srv::GetZ::Response> response) {
  auto x = request->x;
  auto y = request->y;
  double z;
  unsigned int laneID;
  laneutil.getZ(x, y, z, laneID);
  response->z = z;
  response->lane_id = laneID;
}

void GetMapHandler(
    [[maybe_unused]] const std::shared_ptr<
        fead_interfaces::srv::GetMap::Request>
        request,
    std::shared_ptr<fead_interfaces::srv::GetMap::Response> response) {
  std::vector<LaneEdges> laneEdges;
  laneutil.getAllLanes(laneEdges);

  auto map = std::make_shared<fead_interfaces::msg::Map>();

  for (auto& laneEdge : laneEdges) {
    auto lane = std::make_shared<fead_interfaces::msg::Lane>();
    lane->lane_type = static_cast<int32_t>(laneEdge.laneType);
    lane->lane_id = laneEdge.laneID;
    lane->left_edge.edge_type = laneEdge.leftEdgeType;
    lane->right_edge.edge_type = laneEdge.rightEdgeType;

    // left edge waypoints
    for (auto& point : laneEdge.leftEdge) {
      geometry_msgs::msg::Point pt;
      pt.x = point.x;
      pt.y = point.y;
      pt.z = point.z;
      lane->left_edge.waypoints.push_back(pt);
    }

    // right edge waypoints
    for (auto& point : laneEdge.rightEdge) {
      geometry_msgs::msg::Point pt;
      pt.x = point.x;
      pt.y = point.y;
      pt.z = point.z;
      lane->right_edge.waypoints.push_back(pt);
    }

    // add lane to the map
    map->lanes.push_back(*lane);
  }

  response->map = *map;
}

void GetLaneSegmentFromIDHandler(
    const std::shared_ptr<fead_interfaces::srv::GetLaneSegmentFromID::Request>
        request,
    std::shared_ptr<fead_interfaces::srv::GetLaneSegmentFromID::Response>
        response) {
  auto id = request->id;
  map_server::lane::LaneSegmentCPtr seg_ptr =
      laneutil.GetLaneSegmentFromID(id.data);
  if (seg_ptr != nullptr) {
    // auto segment_tmp = *seg_ptr;
    map_server::to_roslanesegment(*seg_ptr, &(response->lane_segment));
  }
}

void GetNearestLaneSegmentsFromPoint3dHandler(
    const std::shared_ptr<
        fead_interfaces::srv::GetNearestLaneSegmentsFromPoint3d::Request>
        request,
    std::shared_ptr<
        fead_interfaces::srv::GetNearestLaneSegmentsFromPoint3d::Response>
        response) {
  // get point
  ::common::math::geom::Point3d query_point;
  map_server::ros2adPoint3d(request->point, &query_point);
  std::cout << " point: ( " << query_point.x << " ," << query_point.y << " ,"
            << query_point.z << std::endl;
  std::vector<std::shared_ptr<map_server::lane::LaneSegment>> lane_segments =
      laneutil.GetNearestLaneSegmentsFromPoint(query_point);
  std::cout << " lane segment size:  " << lane_segments.size() << std::endl;
  if (lane_segments[0] != nullptr) {
    map_server::to_roslanesegment(*lane_segments[0], &(response->lane_segment));
    std::cout << " finish handler  type:  " << lane_segments[0]->type_ad
              << " final type: " << (int)(response->lane_segment.type)
              << std::endl;
    // response->lane_segment = *lane_segment[0];
  }
}

void GetNearestLaneSegmentsFromPoint2dHandler(
    const std::shared_ptr<
        fead_interfaces::srv::GetNearestLaneSegmentsFromPoint2d::Request>
        request,
    std::shared_ptr<
        fead_interfaces::srv::GetNearestLaneSegmentsFromPoint2d::Response>
        response) {
  // get point
  ::common::math::geom::Point2d query_point;
  map_server::ros2adPoint2d(request->point, &query_point);

  std::vector<std::shared_ptr<map_server::lane::LaneSegment>> lane_segment =
      laneutil.GetNearestLaneSegmentsFromPoint(query_point);
  if (lane_segment[0] != nullptr) {
    map_server::to_roslanesegment(*lane_segment[0], &(response->lane_segment));
    // response->lane_segment = *lane_segment[0];
  }
}

void GetNearestCenterPolylinePoint3dHandler(
    const std::shared_ptr<
        fead_interfaces::srv::GetNearestCenterPolylinePoint3d::Request>
        request,
    std::shared_ptr<
        fead_interfaces::srv::GetNearestCenterPolylinePoint3d::Response>
        response) {
  // get lane_id
  std::string lane_id;
  map_server::ros2adString(request->lane_id, &lane_id);

  // get 3d point
  ::common::math::geom::Point3d query_point;
  map_server::ros2adPoint3d(request->point, &query_point);

  std::unique_ptr<map_server::lane::CenterPolylinePoint> tpoint =
      laneutil.GetNearestCenterPolylinePoint(lane_id, query_point);
  if (tpoint != nullptr) {
    map_server::to_rosCenterPolylinePoint(*tpoint,
                                          &(response->center_polyline_point));
    // reponse->center_polyline_point = tpoint;
  }
}

void GetNearestCenterPolylinePoint2dHandler(
    const std::shared_ptr<
        fead_interfaces::srv::GetNearestCenterPolylinePoint2d::Request>
        request,
    std::shared_ptr<
        fead_interfaces::srv::GetNearestCenterPolylinePoint2d::Response>
        response) {
  // // get lane_id
  std::string lane_id;
  map_server::ros2adString(request->lane_id, &lane_id);

  // get point2d
  ::common::math::geom::Point2d query_point;
  map_server::ros2adPoint2d(request->point, &query_point);

  std::unique_ptr<map_server::lane::CenterPolylinePoint> tpoint =
      laneutil.GetNearestCenterPolylinePoint(lane_id, query_point);
  if (tpoint != nullptr) {
    map_server::to_rosCenterPolylinePoint(*tpoint,
                                          &(response->center_polyline_point));
    // reponse->center_polyline_point = *tpoint;
  }
}

void GetFrenetProjectionCenterPolyline3dHandler(
    const std::shared_ptr<
        fead_interfaces::srv::GetFrenetProjectionCenterPolyline3d::Request>
        request,
    std::shared_ptr<
        fead_interfaces::srv::GetFrenetProjectionCenterPolyline3d::Response>
        response) {
  // get lane_segment_id
  std::string lane_segment_id;
  map_server::ros2adString(request->lane_segment_id, &lane_segment_id);

  // get point3d
  ::common::math::geom::Point3d proj_point;
  map_server::ros2adPoint3d(request->proj_point, &proj_point);

  // // GetFrenetProjectionCenterPolyline
  std::unique_ptr<::common::math::geom::ProjectedPoint2d> projected_point2d =
      laneutil.GetFrenetProjectionCenterPolyline(lane_segment_id, proj_point);
  if (projected_point2d != nullptr) {
    map_server::to_rosProjectPoint(*projected_point2d,
                                   &(response->projected_point2d));
    // response->projected_point2d = *projected_point2d;
  }
}

void GetFrenetProjectionCenterPolyline2dHandler(
    const std::shared_ptr<
        fead_interfaces::srv::GetFrenetProjectionCenterPolyline2d::Request>
        request,
    std::shared_ptr<
        fead_interfaces::srv::GetFrenetProjectionCenterPolyline2d::Response>
        response) {
  // get lane_segment_id
  std::string lane_segment_id;
  map_server::ros2adString(request->lane_segment_id, &lane_segment_id);

  // get point2d
  ::common::math::geom::Point2d proj_point;
  map_server::ros2adPoint2d(request->proj_point, &proj_point);
  
  // GetFrenetProjectionCenterPolyline
  std::unique_ptr<::common::math::geom::ProjectedPoint2d> projected_point2d =
      laneutil.GetFrenetProjectionCenterPolyline(lane_segment_id, proj_point);
  if (projected_point2d != nullptr) {
    map_server::to_rosProjectPoint(*projected_point2d,
                                   &(response->projected_point2d));
    // response->projected_point2d = *projected_point2d;
  }
}

class MapServerNode : public rclcpp::Node {
 public:
  MapServerNode() : Node("ad_map_server") {
    srv_routing = this->create_service<fead_interfaces::srv::Routing>(
        "Routing", &RoutingHandler);
    srv_accessLaneID = this->create_service<fead_interfaces::srv::AccessLaneID>(
        "AccessLaneID", &AccessLaneIDHandler);
    srv_accessLeftLane =
        this->create_service<fead_interfaces::srv::AccessLeftLane>(
            "AccessLeftLane", &AccessLeftLaneHandler);
    srv_accessRightLane =
        this->create_service<fead_interfaces::srv::AccessRightLane>(
            "AccessRightLane", &AccessRightLaneHandler);
    srv_getSlop = this->create_service<fead_interfaces::srv::GetSlop>(
        "GetSlop", &GetSlopHandler);
    srv_getZ =
        this->create_service<fead_interfaces::srv::GetZ>("GetZ", &GetZHandler);
    srv_getMap = this->create_service<fead_interfaces::srv::GetMap>(
        "GetMap", &GetMapHandler);

    srv_getLaneSegmentFromID =
        this->create_service<fead_interfaces::srv::GetLaneSegmentFromID>(
            "GetLaneSegmentFromID", &GetLaneSegmentFromIDHandler);
    srv_getNearestLaneSegmentsFromPoint3d = this->create_service<
        fead_interfaces::srv::GetNearestLaneSegmentsFromPoint3d>(
        "GetNearestLaneSegmentsFromPoint3d",
        &GetNearestLaneSegmentsFromPoint3dHandler);
    srv_getNearestLaneSegmentsFromPoint2d = this->create_service<
        fead_interfaces::srv::GetNearestLaneSegmentsFromPoint2d>(
        "GetNearestLaneSegmentsFromPoint2d",
        &GetNearestLaneSegmentsFromPoint2dHandler);
    srv_getNearestCenterPolylinePoint3d = this->create_service<
        fead_interfaces::srv::GetNearestCenterPolylinePoint3d>(
        "GetNearestCenterPolylinePoint3d",
        &GetNearestCenterPolylinePoint3dHandler);
    srv_getNearestCenterPolylinePoint2d = this->create_service<
        fead_interfaces::srv::GetNearestCenterPolylinePoint2d>(
        "GetNearestCenterPolylinePoint2d",
        &GetNearestCenterPolylinePoint2dHandler);
    srv_getFrenetProjectionCenterPolyline3d = this->create_service<
        fead_interfaces::srv::GetFrenetProjectionCenterPolyline3d>(
        "GetFrenetProjectionCenterPolyline3d",
        &GetFrenetProjectionCenterPolyline3dHandler);
    srv_getFrenetProjectionCenterPolyline2d = this->create_service<
        fead_interfaces::srv::GetFrenetProjectionCenterPolyline2d>(
        "GetFrenetProjectionCenterPolyline2d",
        &GetFrenetProjectionCenterPolyline2dHandler);
  }

 private:
  rclcpp::Service<fead_interfaces::srv::Routing>::SharedPtr srv_routing;
  rclcpp::Service<fead_interfaces::srv::AccessLaneID>::SharedPtr
      srv_accessLaneID;
  rclcpp::Service<fead_interfaces::srv::AccessLeftLane>::SharedPtr
      srv_accessLeftLane;
  rclcpp::Service<fead_interfaces::srv::AccessRightLane>::SharedPtr
      srv_accessRightLane;
  rclcpp::Service<fead_interfaces::srv::GetSlop>::SharedPtr srv_getSlop;
  rclcpp::Service<fead_interfaces::srv::GetZ>::SharedPtr srv_getZ;
  rclcpp::Service<fead_interfaces::srv::GetMap>::SharedPtr srv_getMap;
  rclcpp::Service<fead_interfaces::srv::GetLaneSegmentFromID>::SharedPtr
      srv_getLaneSegmentFromID;
  rclcpp::Service<fead_interfaces::srv::GetNearestLaneSegmentsFromPoint3d>::
      SharedPtr srv_getNearestLaneSegmentsFromPoint3d;
  rclcpp::Service<fead_interfaces::srv::GetNearestLaneSegmentsFromPoint2d>::
      SharedPtr srv_getNearestLaneSegmentsFromPoint2d;
  rclcpp::Service<fead_interfaces::srv::GetNearestCenterPolylinePoint3d>::
      SharedPtr srv_getNearestCenterPolylinePoint3d;
  rclcpp::Service<fead_interfaces::srv::GetNearestCenterPolylinePoint2d>::
      SharedPtr srv_getNearestCenterPolylinePoint2d;
  rclcpp::Service<fead_interfaces::srv::GetFrenetProjectionCenterPolyline3d>::
      SharedPtr srv_getFrenetProjectionCenterPolyline3d;
  rclcpp::Service<fead_interfaces::srv::GetFrenetProjectionCenterPolyline2d>::
      SharedPtr srv_getFrenetProjectionCenterPolyline2d;
};

int main(int argc, char* argv[]) {
  // maputil.initialize("/home/jiaping/code/fead_ws/src/hdmap/ad_map/ad_map_server/src/HDMAP/Town06_config.txt");
  // maputil.initialize(argv[1]);
  laneutil.initialize(argv[1]);
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MapServerNode>());
  rclcpp::shutdown();
  return 0;
}
