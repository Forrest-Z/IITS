#include "ad_to_ros_msg.h"

// #include <std_msgs/msg/float_t.h>

namespace map_server {

void to_rosId(const std::string &in, std_msgs::msg::String *out) {
  out->data = in;
}
void to_rosPoint(const common::math::geom::Point3d &in_point3,
                 geometry_msgs::msg::Point *out_point) {
  out_point->x = in_point3.x;
  out_point->y = in_point3.y;
  out_point->z = in_point3.z;
}

void to_rosPoint2d(const common::math::geom::Point2d &in_point2,
                   fead_interfaces::msg::Point2d *out_point2d) {
  out_point2d->x = in_point2.x;
  out_point2d->y = in_point2.y;
}

void to_rosProjectPoint(
    const ::common::math::geom::ProjectedPoint2d &in_projectpt,
    fead_interfaces::msg::ProjectedPoint2d *out_projectpt) {
  to_rosPoint2d(in_projectpt.proj_pt, &(out_projectpt->proj_pt));
  out_projectpt->frenet_pt.s = in_projectpt.frenet_pt.s;
  out_projectpt->frenet_pt.l = in_projectpt.frenet_pt.l;
}
void to_rosCenterPolylinePoint(
    const map_server::lane::CenterPolylinePoint &in_centerpolylinept,
    fead_interfaces::msg::CenterPolylinePoint *out_polylinept) {
  to_rosPoint(in_centerpolylinept.pt, &(out_polylinept->pt));
  out_polylinept->left_width_m = in_centerpolylinept.left_width_m;
  out_polylinept->right_width_m = in_centerpolylinept.right_width_m;
  out_polylinept->accumulated_s_m = in_centerpolylinept.accumulated_s_m;
}
void to_rosLaneBoundary(const map_server::lane::LaneBoundary &in_laneboundary,
                        fead_interfaces::msg::LaneBoundary *out_laneboundary) {
  out_laneboundary->polyline_type =
      static_cast<uint8_t>(in_laneboundary.polyline_type);

  for (size_t i = 0; i < in_laneboundary.polyline.size(); ++i) {
    geometry_msgs::msg::Point ros_point;
    to_rosPoint(in_laneboundary.polyline[i], &ros_point);
    out_laneboundary->polyline.points.push_back(ros_point);
  }
}

void to_rosStringVector(const std::vector<std::string> &in_string_vector,
                        std::vector<std_msgs::msg::String> *out_string_vector) {
  for (auto &str : in_string_vector) {
    std_msgs::msg::String msg;
    msg.data = str;
    out_string_vector->push_back(msg);
  }
}

void to_roscenter_polyline(
    const map_server::lane::CenterPolyline &in_center_polyline,
    fead_interfaces::msg::CenterPolyline *out_polyline) {
  for (auto &polylinept : in_center_polyline.points) {
    fead_interfaces::msg::CenterPolylinePoint ros_poly_line_pt;
    to_rosCenterPolylinePoint(polylinept, &ros_poly_line_pt);
    out_polyline->points.push_back(ros_poly_line_pt);
  }
}

void to_roslanesegment(const map_server::lane::LaneSegment &in_lanesegement,
                       fead_interfaces::msg::LaneSegment *out_lanesegement) {
  to_rosId(in_lanesegement.id, &(out_lanesegement->id));
  out_lanesegement->type = static_cast<uint8_t>(
      map_server::convertLaneType(in_lanesegement.type_ad));
  out_lanesegement->lane_turn = static_cast<uint8_t>(in_lanesegement.lane_turn);
  to_rosLaneBoundary(in_lanesegement.left_boundary,
                     &(out_lanesegement->left_boundary));
  to_rosLaneBoundary(in_lanesegement.right_boundary,
                     &(out_lanesegement->right_boundary));
  to_rosStringVector(in_lanesegement.predecessor_ids,
                     &(out_lanesegement->predecessor_ids));
  to_rosStringVector(in_lanesegement.successor_ids,
                     &(out_lanesegement->successor_ids));
  to_rosStringVector(in_lanesegement.left_neighbor_ids,
                     &(out_lanesegement->left_neighbor_ids));
  to_rosStringVector(in_lanesegement.right_neighbor_ids,
                     &(out_lanesegement->right_neighbor_ids));
  out_lanesegement->speed_limit_min_mps = in_lanesegement.speed_limit_min_mps;
  out_lanesegement->speed_limit_max_mps = in_lanesegement.speed_limit_max_mps;
  to_roscenter_polyline(in_lanesegement.center_polyline,
                        &(out_lanesegement->center_polyline));
  to_rosStringVector(in_lanesegement.traffic_light_ids,
                     &(out_lanesegement->traffic_light_ids));
}

}  // namespace map_server