

#ifndef HDMAP_AD_MAP_AD_MAP_SERVER_TO_ROSMSG_H_
#define HDMAP_AD_MAP_AD_MAP_SERVER_TO_ROSMSG_H_

#include "center_polyline.h"
#include "common/math/geom/frenet_point.h"
#include "common/math/geom/vec3.h"
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

void to_rosId(const std::string &in, std_msgs::msg::String *out);

void to_rosPoint(const common::math::geom::Point3d &in_point3,
                 geometry_msgs::msg::Point *out_point);
void to_rosPoint2d(const common::math::geom::Point2d &in_point2,
                   fead_interfaces::msg::Point2d *out_point2d);
// void to_rosFrenetPoint(const common::math::geom::FrenetPoint &in_FNpt,
//                        fead_interfaces::msg::FrenetPoint *out_PNpt);
void to_rosProjectPoint(
    const ::common::math::geom::ProjectedPoint2d &in_projectpt,
    fead_interfaces::msg::ProjectedPoint2d *out_projectpt);
void to_rosCenterPolylinePoint(
    const map_server::lane::CenterPolylinePoint &in_centerpolylinept,
    fead_interfaces::msg::CenterPolylinePoint *out_polylinept);

void to_rosLaneBoundary(const map_server::lane::LaneBoundary &in_laneboundary,
                        fead_interfaces::msg::LaneBoundary *out_laneboundary);
void to_rosStringVector(const std::vector<std::string> &in_string_vector,
                        std::vector<std_msgs::msg::String> *out_string_vector);
void to_roscenter_polyline(
    const map_server::lane::CenterPolyline &in_center_polyline,
    fead_interfaces::msg::CenterPolyline *out_polyline);

void to_roslanesegment(const map_server::lane::LaneSegment &in_lanesegement,
                       fead_interfaces::msg::LaneSegment *out_lanesegement);

}  // namespace map_server

#endif  //