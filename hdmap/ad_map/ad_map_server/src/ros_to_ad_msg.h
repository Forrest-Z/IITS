#ifndef HDMAP_AD_MAP_AD_MAP_SERVER_ROS_TO_AD_MSG_H_
#define HDMAP_AD_MAP_AD_MAP_SERVER_ROS_TO_AD_MSG_H_

#include <geometry_msgs/msg/point.hpp>

#include "center_polyline.h"
#include "converter.h"
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
#include "lane_segment.h"
#include "map_util.h"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

namespace map_server {
void ros2adString(const std_msgs::msg::String &in, std::string *out) {
  *out = in.data;
}

void ros2adPoint2d(const fead_interfaces::msg::Point2d &in,
                   ::common::math::geom::Point2d *out) {
  *out = ::common::math::geom::Point2d(in.x, in.y);
}

void ros2adPoint3d(const geometry_msgs::msg::Point &in,
                   ::common::math::geom::Point3d *out) {
  *out = ::common::math::geom::Point3d(in.x, in.y, in.z);
}

}  // namespace map_server

#endif