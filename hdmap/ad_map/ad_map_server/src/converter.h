//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//

#ifndef HDMAP_AD_MAP_AD_MAP_SERVER_CONVERTER_H_
#define HDMAP_AD_MAP_AD_MAP_SERVER_CONVERTER_H_

#include <string>

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
#include "lane_utils.h"
#include "opendrive/OpenDrive.hpp"

using namespace ::ad;
using namespace ::ad::map;
using namespace ::ad::map::point;

namespace map_server {
// convert ID: int to string
std::string convertID(const int& id);

int convertID(const std::string& id);

ENUPoint convertPoint(const ::common::math::geom::Point3d& point);

// convert lane type: lane:LaneType to laneSegment Type
lane::LaneSegment::Type convertLaneType(::ad::map::lane::LaneType type);

// convert contact lanes
void convertContactLanes(const ::ad::map::lane::ContactLaneList& contactList,
                         std::vector<std::string>& predecessor_ids,
                         std::vector<std::string>& successor_ids,
                         std::vector<std::string>& left_neighbor_ids,
                         std::vector<std::string>& right_neighbor_ids);

// convert boundary:
lane::LaneBoundary convertEdge(const ::ad::map::point::Geometry& edge);

::common::math::geom::SimplePolygon2d ConvertLaneSegmentToPolygon(
    const std::shared_ptr<map_server::lane::LaneSegment> lane_segment);

void convertSpeedLimits(
    const ::ad::map::restriction::SpeedLimitList& speedLimits,
    double& speed_limit_min_mps, double& speed_limit_max_mps);

lane::CenterPolyline convertCenterPolyline(
    const lane::LaneBoundary& leftBoundary,
    const lane::LaneBoundary& rightBoundary);

}  // namespace map_server

#endif