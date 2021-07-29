//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//

#ifndef HDMAP_AD_MAP_AD_MAP_SERVER_LANE_BOUNDARY_H_
#define HDMAP_AD_MAP_AD_MAP_SERVER_LANE_BOUNDARY_H_

#include <memory>
#include <vector>

#include "common/math/geom/geom_utils.h"
// #include "common/style_type.h"

namespace map_server {
namespace lane {
///
/// @class LaneBoundary: the  lane boundary class
/// refer to
/// https://gitlab.rd.inceptioglobal.ai/autonomy/cybertron/-/blob/master/hdmap/lane_graph/lane_boundary.h
///
class LaneBoundary {
 public:
  //
  // @enum LineType: define the type/style for a polyline/polygon boundary
  //
  enum LineType {
    // All the line style i initialized to UNDEFINED
    LINE_TYPE_UNDEFINED = 0,

    // most common type for polyline
    SINGLE_SOLID = 1,
    SINGLE_DASHED = 2,
    SINGLE_DOTTED = 3,
    DOUBLE_SOLID = 4,
    DOUBLE_DASHED = 5,
    DOUBLE_DOTTED = 6,

    // Max line type for software safety
    MAX_LINE_TYPE = 7
  };

 public:
  // BoundaryType type;
  // Defined in WGS-84 coordinate system.
  ::common::math::geom::Polyline3d polyline;
  // ColorType polyline_color;
  LineType polyline_type;
};

}  // namespace lane
}  // namespace map_server

#endif  // HDMAP_AD_MAP_AD_MAP_SERVER_LANE_BOUNDARY_H_
