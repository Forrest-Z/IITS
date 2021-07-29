
import sys
import os
import math
import numpy as np

from ament_index_python.packages import get_package_prefix, get_package_share_directory

sys.path.append(os.path.join(get_package_prefix('ad_map_access'), 'lib'))
sys.path.append(os.path.join(get_package_prefix('ad_physics'), 'lib'))
resource_dir = get_package_share_directory('ad_map_server_py')

if sys.version_info.major == 3:
    import libad_physics_python3 as physics
    import libad_map_access_python3 as admap
else:
    import libad_physics_python2 as physics
    import libad_map_access_python2 as admap

class Singleton(object):
    def __init__(self, cls):
        self._cls = cls
        self._instance = {}
    def __call__(self):
        if self._cls not in self._instance:
            self._instance[self._cls] = self._cls()
        return self._instance[self._cls]

@Singleton
class CoordTrans(object):
    def __init__(self, delta_x = 0.0, delta_y = 0.0, delta_z = 0.0):
        self.delta_x = delta_x
        self.delta_y = delta_y
        self.delta_z = delta_z
        # TODO : remove default value here
        self.set_delta(-225.151904, -6337.384475)

    def set_delta(self, delta_x, delta_y, delta_z = 0.0):
        self.delta_x = delta_x
        self.delta_y = delta_y
        self.delta_z = delta_z

    def trucksim_to_map(self, pos):
        if len(pos) == 2:
            return [pos[0] + self.delta_x, pos[1] + self.delta_y]
        elif len(pos) == 3:
            return [pos[0] + self.delta_x, pos[1] + self.delta_y, pos[2]]

    def trucksim_to_carla(self, pos):
        if len(pos) == 2:
            return [pos[0] + self.delta_x, -(pos[1] + self.delta_y)]
        elif len(pos) == 3:
            return [pos[0] + self.delta_x, -(pos[1] + self.delta_y), pos[2]]
    
    def carla_to_map(self, pos):
        if len(pos) == 2:
            return [pos[0], -pos[1]]
        elif len(pos) == 3:
            return [pos[0], -pos[1], pos[2]]
    
    def map_to_trucksim(self, pos):
        if len(pos) == 2:
            return [pos[0] - self.delta_x, pos[1] - self.delta_y]
        elif len(pos) == 3:
            return [pos[0] - self.delta_x, pos[1] - self.delta_y, pos[2]]
    
    def map_to_carla(self, pos):
        if len(pos) == 2:
            return [pos[0], -pos[1]]
        elif len(pos) == 3:
            return [pos[0], -pos[1], pos[2]]

def toENUPoint(xyz):
    if len(xyz) == 2:
        return admap.createENUPoint(xyz[0], xyz[1], 0.0)
    elif len(xyz) == 3:
        return admap.createENUPoint(xyz[0], xyz[1], xyz[2])
    else:
        return None

def findParaPoint(xyz):
    pt_enu = toENUPoint(xyz)
    pt_match = mapMatching.getMapMatchedPositions(
            pt_enu, physics.Distance(10.0), physics.Probability(0.05))
    if len(pt_match) > 0:
        # use nearest point
        pt_para = pt_match[0].lanePoint.paraPoint
    
    print(pt_para.parametricOffset)

@Singleton
class MapServer():
    def __init__(self, map_dir = os.path.join(resource_dir, 'jinan_config.txt')):
        self.map_dir = map_dir
        admap.init(self.map_dir)

def compute_distance(p1, p2):
    p1 = np.array(p1)
    p2 = np.array(p2)
    dist = np.linalg.norm(p1-p2)
    return dist

def compute_distance_ECEF(p1, p2):
    p1 = admap.toENU(p1)
    p2 = admap.toENU(p2)
    pp1 = [float(p1.x), float(p1.y), float(p1.z)]
    pp2 = [float(p2.x), float(p2.y), float(p2.z)]
    return compute_distance(pp1, pp2)

def opendrive_to_xyz(map_dir, start_pt, end_pt):
    admap.init(map_dir)

    start_pt = toENUPoint(start_pt)
    end_pt = toENUPoint(end_pt)

    mapMatching = admap.AdMapMatching()
    start_map_matches = mapMatching.getMapMatchedPositions(
            start_pt, physics.Distance(10.0), physics.Probability(0.05))
    assert len(start_map_matches) > 0
    # use nearest point
    start_pt_para = start_map_matches[0].lanePoint.paraPoint

    end_map_matches = mapMatching.getMapMatchedPositions(
            end_pt, physics.Distance(10.0), physics.Probability(0.05))
    assert len(end_map_matches) > 0
    end_pt_para = end_map_matches[0].lanePoint.paraPoint

    route_result = admap.planRoute(start_pt_para, end_pt_para, admap.RouteCreationMode.SameDrivingDirection)
    roads = route_result.roadSegments

    route_lanes = []

    for r_idx, road in enumerate(roads):
        lanes = road.drivableLaneSegments
        ret = str(len(lanes)) + ' : '
        for l_idx, laneSeg in enumerate(lanes):
            #lane = lanes[0]
            lane_interval = laneSeg.laneInterval
            lane_id = laneSeg.laneInterval.laneId
            lane_offset = laneSeg.routeLaneOffset
            lane = admap.getLane(lane_id)
            #print(lane_interval.start, lane_interval.end)
            ret += str(lane_id) + ' ' + str(lane_offset) + ' ' \
            + str(lane.type) + ' ' \
            + str(lane_interval.start) + ' ' \
            + str(lane_interval.end) + ' ' \
            ', '

            if (lane_offset == 0):
                route_lanes.append(lane)
        #print(ret)

    waypoint = []
    delta_dist_meter = 1.0
    last_point = np.array([])
    for lane_idx, lane in enumerate(route_lanes):
        tlen = lane.length
        delta_para = delta_dist_meter / float(tlen)
        t_para = 0.0
        while t_para <= 1.0:
            point_para = admap.createParaPoint(lane.id, physics.ParametricValue(t_para))
            t_para = t_para + delta_para

            #point_para = admap.createParaPoint(lane, physics.ParametricValue(t_para))
            point_enu_left_edge = admap.getENULanePoint(point_para, 0)
            #print(point_enu_left_edge)
            pt = np.array([float(point_enu_left_edge.x), float(point_enu_left_edge.y), float(point_enu_left_edge.z)])
            if last_point.size != 0:
                distance = np.linalg.norm(pt - last_point)
                if distance <= 0.9:
                    continue

            last_point = pt
            waypoint.append(pt)
            

    print(len(waypoint), ' : ', waypoint[0])
    waypoint_shift = [(w - waypoint[0]) for w in waypoint ]

    np.savetxt('/home/liwei/Desktop/jinan/jinan_xyz_check_y.txt', waypoint_shift, fmt='%.6f')


    '''
    #### lane
    # base point 
    base_point = admap.toENU(route_lanes[0].edgeLeft.ecefEdge[0])
    prev_point = base_point
    find_zig = False
    with open('jinan.xyz', 'w') as f_xyz:
        for lane_id, lane in enumerate(route_lanes):
            if lane_id == 0:
                find_zig = True
            else:
                find_zig = False

            left_edge = lane.edgeLeft.ecefEdge
            for pt_idx, pt in enumerate(left_edge):

                if find_zig == False:
                    # do check distance
                    d = compute_distance_ECEF(pt, prev_point)
                    if d < 5:
                        continue
                    else:
                        find_zig = True

                prev_point = pt
                pt = admap.toENU(pt)
                #print(pt)
                pt.x = pt.x - base_point.x
                pt.y = pt.y - base_point.y
                pt.z = pt.z - base_point.z
                #print('{0} {1} {2}\r\n'.format(pt.x, pt.y, pt.z))
                f_xyz.write('{0} {1} {2}\r\n'.format(pt.x, pt.y, pt.z))
    '''
                

def test():
    MapServer()
    coord_trans = CoordTrans()

    start_pt = [-170.513, 102.104475, 295.313]
    end_pt = [925.421904, 12945.254435, 408.727]

    start_pt = coord_trans.trucksim_to_map(start_pt)
    end_pt = coord_trans.trucksim_to_map(end_pt)

    start_pt = [-834.719,-5942.98,299.722]
    end_pt = [-987.523,-5743.54,303.377]
 
    start_pt = toENUPoint(start_pt)
    end_pt = toENUPoint(end_pt)

    mapMatching = admap.AdMapMatching()
    start_map_matches = mapMatching.getMapMatchedPositions(
            start_pt, physics.Distance(10.0), physics.Probability(0.05))
    assert len(start_map_matches) > 0
    # use nearest point
    start_pt_para = start_map_matches[0].lanePoint.paraPoint

    end_map_matches = mapMatching.getMapMatchedPositions(
            end_pt, physics.Distance(10.0), physics.Probability(0.05))
    assert len(end_map_matches) > 0
    end_pt_para = end_map_matches[0].lanePoint.paraPoint

    route_result = admap.planRoute(start_pt_para, end_pt_para, admap.RouteCreationMode.SameDrivingDirection)
    roads = route_result.roadSegments

    # findWaypoint(point::ParaPoint const &position, route::FullRoute const &route);

    # pt_enu = toENUPoint([-535.598, -6153.718, 293.584])
    # pt_match = mapMatching.getMapMatchedPositions(
    #         pt_enu, physics.Distance(10.0), physics.Probability(0.05))
    # assert len(pt_match) > 0
    # # use nearest point
    # pt_para = pt_match[0].lanePoint.paraPoint
    
    # print(pt_para.parametricOffset)

    for r_idx, road in enumerate(roads):
        lanes = road.drivableLaneSegments
        ret = str(len(lanes)) + ' : '
        for l_idx, laneSeg in enumerate(lanes):
            #lane = lanes[0]
            lane_interval = laneSeg.laneInterval
            lane_id = laneSeg.laneInterval.laneId
            lane_offset = laneSeg.routeLaneOffset
            lane = admap.getLane(lane_id)
            #print(lane_interval.start, lane_interval.end)
            ret += str(lane_id) + ' ' + str(lane_offset) + ' ' \
            + str(lane.type) + ' ' \
            + str(lane_interval.start) + ' ' \
            + str(lane_interval.end) + ' ' \
            ', '

        #print(ret)

        #print(lane_id, lane_offset)

        #pt = admap.getLaneParaPoint(physics.ParametricValue(1.0), lane.laneInterval)

        #print(admap.getLaneParaPoint(physics.ParametricValue(1), lane.laneInterval))
    
    

    # point::ParaPoint getLaneParaPoint(physics::ParametricValue const &routeParametricOffset,
    #                               route::LaneInterval const &laneInterval);

    print('done')


    #route::FullRoute routeResult = route::planning::planRoute(ENU2PARA(startPoint),ENU2PARA(endPoint),route::RouteCreationMode::Undefined);
    #route::RoadSegmentList roads = routeResult.roadSegments;


if __name__ == '__main__':
    map_dir = os.path.join(resource_dir, 'jinan_config.txt')
    #map_dir = '/home/liwei/Desktop/jinan/2020-09-04-jinan-with-overlap-subtract-mean.xodr'
    #map_dir = '/home/liwei/Desktop/jinan/jinan_config.txt'
    #map_dir = '/mnt/data/code/fead/fead_ws/src/hdmap/ad_map/ad_map_server/resource/jinan_config_overlap.txt'
    
    start_point = [-230.375290, -6345.953613, 297.901367]
    end_point = [682.973145, 6679.187500, 408.427643]
    opendrive_to_xyz(map_dir, start_point, end_point)
