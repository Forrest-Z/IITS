//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//

#ifndef HDMAP_AD_MAP_AD_MAP_SERVER_CENTER_POLYLINE_H_
#define HDMAP_AD_MAP_AD_MAP_SERVER_CENTER_POLYLINE_H_

#include <memory>
#include <vector>

#include "common/math/geom/geom_utils.h"

namespace map_server {
namespace lane {

// refer to
// https://gitlab.rd.inceptioglobal.ai/autonomy/cybertron/-/blob/master/hdmap/lane_graph/lane_segment.h

///
/// @class CenterPolylinePoint: the center polyline point.
///

class CenterPolylinePoint {
 public:
  // The center polylin point coordiante in m.
  ::common::math::geom::Point3d pt;

  // The left/right lane width in m.
  double left_width_m;
  double right_width_m;

  // The accumulated s in m.
  double accumulated_s_m;
};

///
/// @class CenterPolyline: the center polyline
///
class CenterPolyline {
 public:
  CenterPolyline(){};
  ~CenterPolyline(){};
  /// @brief TotalLength: the total length of the center polyline
  double TotalLength() const {};

  /// @brief ToPolyline: convert to math polyline
  ::common::math::geom::Polyline3d ToPolyline() const {
    std::vector<::common::math::geom::Point3d> tpoints;
    for (size_t i = 0; i < points.size(); i++) {
      tpoints.push_back(points[i].pt);
    }
    return ::common::math::geom::Polyline3d(tpoints);
  };

  /// @brief ToPoint3dVector: conver to vector of points
  std::vector<::common::math::geom::Point3d> ToPoint3dVector() const {};

  /// @brief ToPoint2dVector: convert to vector of points
  std::vector<::common::math::geom::Point2d> ToPoint2dVector() const {};

 public:
  std::vector<CenterPolylinePoint> points;
};

}  // namespace lane
}  // namespace map_server

#endif  // HDMAP_AD_MAP_AD_MAP_SERVER_CENTER_POLYLINE_H_