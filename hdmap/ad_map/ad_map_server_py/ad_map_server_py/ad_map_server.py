
import sys
import os
import math
import numpy as np
from collections import deque

from ament_index_python.packages import get_package_prefix, get_package_share_directory
# from trajectory_planner.coord_tranform import Coord_Trans

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
    def __init__(self, delta_x=0.0, delta_y=0.0, delta_z=0.0):
        self.delta_x = delta_x
        self.delta_y = delta_y
        self.delta_z = delta_z
        # # TODO : remove default value here
        # self.set_delta(-225.151904, -6337.384475)

    def set_delta(self, delta_x, delta_y, delta_z=0.0):
        self.delta_x = delta_x
        self.delta_y = delta_y
        self.delta_z = delta_z

    def trucksim_to_map(self, pos):
        if len(pos) == 2:
            return [pos[0] + self.delta_x, pos[1] + self.delta_y]
        elif len(pos) == 3:
            return [pos[0] + self.delta_x, pos[1] + self.delta_y, pos[2] + self.delta_z]

    def trucksim_to_carla(self, pos):
        if len(pos) == 2:
            return [pos[0] + self.delta_x, -(pos[1] + self.delta_y)]
        elif len(pos) == 3:
            return [pos[0] + self.delta_x, -(pos[1] + self.delta_y), pos[2] + self.delta_z]

    def carla_to_map(self, pos):
        if len(pos) == 2:
            return [pos[0], -pos[1]]
        elif len(pos) == 3:
            return [pos[0], -pos[1], pos[2]]

    def map_to_trucksim(self, pos):
        if len(pos) == 2:
            return [pos[0] - self.delta_x, pos[1] - self.delta_y]
        elif len(pos) == 3:
            return [pos[0] - self.delta_x, pos[1] - self.delta_y, pos[2] - self.delta_z]

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
    def __init__(self, map_dir=os.path.join(resource_dir, 'jinan_two_lanes_config.txt')):
        self.coord_trans = CoordTrans()
        #self.coord_trans.set_delta(-225.151904, -6337.384475)
        # self.coord_trans.set_delta(-230.3752885, -6345.95359709, 297.90137)
        # our trucksim model
        # self.coord_trans.set_delta(-230.3752885, -6345.95359709, 296.90137)

        # Run_cnhtc_pre_a_v1p1_jinan_all
        self.coord_trans.set_delta(-563.4263999999966, -
                                   6132.508499999996, 294.0342)

        self.map_dir = map_dir
        admap.init(self.map_dir)

    def toENUPoint(self, xyz):
        try:
            if len(xyz) == 2:
                return admap.createENUPoint(xyz[0], xyz[1], 0.0)
            elif len(xyz) == 3:
                return admap.createENUPoint(xyz[0], xyz[1], xyz[2])
            else:
                return None
        except:
            print("error point")
            return None

    def toECEFPoint(self, xyz):
        if len(xyz) == 2:
            return admap.createECEFPoint(xyz[0], xyz[1], 0.0)
        elif len(xyz) == 3:
            return admap.createECEFPoint(xyz[0], xyz[1], xyz[2])
        else:
            return None

    def ECEF_to_ENU(self, ecef_point):
        enu_point = admap.toENU(ecef_point)
        return [enu_point.x, enu_point.y, enu_point.z]

    def find_lane_id(self, pos):
        pt = self.toENUPoint(pos)
        mapMatching = admap.AdMapMatching()
        car_map_matches = mapMatching.getMapMatchedPositions(
            pt, physics.Distance(10.0), physics.Probability(0.05))

        if not len(car_map_matches) > 0:
            return None
        # use nearest point
        car_pt_para = car_map_matches[0].lanePoint.paraPoint
        car_lane_id = car_pt_para.laneId
        return car_lane_id

    def find_lc_lanes(self, car_pos, lc_op, check_dist):
        succ_lanes_list = self.find_infront_lanes(car_pos, check_dist)
        lc_lanes = []
        for tlane in succ_lanes_list:
            try:
                if lc_op == -1:  # left
                    left_lane = admap.getLane(admap.getContactLanes(
                        tlane, admap.ContactLocation(2))[0].toLane)
                    lc_lanes.append(left_lane)
                elif lc_op == 1:  # right
                    right_lane = admap.getLane(admap.getContactLanes(
                        tlane, admap.ContactLocation(3))[0].toLane)
                    lc_lanes.append(right_lane)
                else:
                    pass
            except:
                pass

        return lc_lanes

    def find_back_neighbor_lanes(self, car_pos, check_dist):
        candidiate_list = []
        succ_lanes_list = self.find_back_lanes(car_pos, check_dist)
        for tlane in succ_lanes_list:
            try:
                left_lane = admap.getLane(admap.getContactLanes(
                    tlane, admap.ContactLocation(2))[0].toLane)
                candidiate_list.append(left_lane)
            except:
                pass
            try:
                right_lane = admap.getLane(admap.getContactLanes(
                    tlane, admap.ContactLocation(3))[0].toLane)
                candidiate_list.append(right_lane)
            except:
                pass
            candidiate_list.append(tlane)
        return candidiate_list

    def find_front_neighbor_lanes(self, car_pos, check_dist):
        candidiate_list = []
        succ_lanes_list = self.find_infront_lanes(car_pos, check_dist)
        for tlane in succ_lanes_list:
            try:
                left_lane = admap.getLane(admap.getContactLanes(
                    tlane, admap.ContactLocation(2))[0].toLane)
                candidiate_list.append(left_lane)
            except:
                pass
            try:
                right_lane = admap.getLane(admap.getContactLanes(
                    tlane, admap.ContactLocation(3))[0].toLane)
                candidiate_list.append(right_lane)
            except:
                pass
            candidiate_list.append(tlane)
        return candidiate_list

    def handle_lane_overlap(self, target_lane, previous_end_point):
        ecef_point = admap.toECEF(previous_end_point)
        result = admap.MapMatchedPosition()
        result_flag = admap.findNearestPointOnLane(
            target_lane, ecef_point, result)
        if result_flag:
            return result.lanePoint

    def cal_constv_pt(self, start_pos, end_pos, num_waypt, pt_interval):
        start_pt = self.toENUPoint(start_pos)
        end_pt = self.toENUPoint(end_pos)
        global_plan = deque(maxlen=num_waypt)
        roads = self.GlobalPlanner(start_pt, end_pt)
        tENUPoint = None
        mapMatching = admap.AdMapMatching()
        car_map_matches = mapMatching.getMapMatchedPositions(
            start_pt, physics.Distance(10.0), physics.Probability(0.05))
        assert len(car_map_matches) > 0
        car_pt_para = car_map_matches[0].lanePoint.paraPoint
        car_laneoffset = car_pt_para.parametricOffset
        car_lane_id = car_pt_para.laneId
        tlane = admap.getLane(car_lane_id)
        # tstart_offset = float((car_laneoffset))*float(tlane.length)
        tstart_offset = 0.0
        for i, road in enumerate(roads):
            lanes = road.drivableLaneSegments
            current_lane = lanes[0]
            for lane in lanes:
                if lane.routeLaneOffset == 0:
                    current_lane = lane
                    break
            lane_interval = current_lane.laneInterval
            lane_id = current_lane.laneInterval.laneId
            lane_offset = current_lane.routeLaneOffset
            tlane = admap.getLane(lane_id)
            lane_length = float(tlane.length)
            deltpara = pt_interval/(lane_length)
            tstart = current_lane.laneInterval.start
            tend = current_lane.laneInterval.end
            tstart_offset = tstart_offset/lane_length
            if i > 0 and tENUPoint is not None:
                matched_point = self.handle_lane_overlap(tlane, tENUPoint)
                tstart_offset += float(matched_point.paraPoint.parametricOffset)
            if tstart < tend:
                tPara = tstart + tstart_offset+deltpara
                while tPara <= tend:
                    tParaPoint = admap.createParaPoint(lane_id, tPara)
                    tENUPoint = admap.getENULanePoint(tParaPoint, 0.5)
                    if len(global_plan) < num_waypt:
                        x = float(tENUPoint.x)
                        y = float(tENUPoint.y)
                        z = float(tENUPoint.z)
                        # converted_ord = self.coord_trans.map_to_trucksim([x, y])
                        global_plan.append([x, y, z])
                    else:
                        return global_plan
                    tPara = tPara+deltpara
                    # if tPara>tend:
                    #     tstart_offset = float(tPara - tend)*lane_length
            else:
                tPara = tstart - tstart_offset - deltpara
                while tPara >= tend:
                    tParaPoint = admap.createParaPoint(lane_id, tPara)
                    tENUPoint = admap.getENULanePoint(tParaPoint, 0.5)
                    if len(global_plan) < num_waypt:
                        x = float(tENUPoint.x)
                        y = float(tENUPoint.y)
                        z = float(tENUPoint.z)
                        # converted_ord = self.coord_trans.map_to_trucksim([x, y])
                        global_plan.append([x, y, z])
                    else:
                        return global_plan
                    tPara = tPara-deltpara
                    # if tPara < tend:
                    #     tstart_offset = float(tend-tPara)*lane_length
        return global_plan

    def GlobalPlanner(self, start_pos, end_pos):
        mapMatching = admap.AdMapMatching()
        start_map_matches = mapMatching.getMapMatchedPositions(
            start_pos, physics.Distance(10.0), physics.Probability(0.05))
        assert len(start_map_matches) > 0
        # use nearest point
        start_pt_para = start_map_matches[0].lanePoint.paraPoint

        end_map_matches = mapMatching.getMapMatchedPositions(
            end_pos, physics.Distance(10.0), physics.Probability(0.05))
        assert len(end_map_matches) > 0
        end_pt_para = end_map_matches[0].lanePoint.paraPoint

        rount_result = admap.planRoute(start_pt_para, end_pt_para)
        roads = rount_result.roadSegments
        self.routing_result = roads
        return roads

    def find_infront_lanes(self, car_pos, check_distance):
        succ_lanes_list = []
        sum_dist = 0
        car_pt = self.toENUPoint(car_pos)
        mapMatching = admap.AdMapMatching()
        car_map_matches = mapMatching.getMapMatchedPositions(
            car_pt, physics.Distance(100.0), physics.Probability(0.05))
        if not len(car_map_matches) > 0:
            return []
        # use nearest point
        car_pt_para = car_map_matches[0].lanePoint.paraPoint
        car_lane_id = car_pt_para.laneId
        car_laneoffset = car_pt_para.parametricOffset
        tlane = admap.getLane(car_lane_id)
        sum_dist += (1-float(car_laneoffset))*float(tlane.length)
        succ_lanes_list.append(tlane)
        while sum_dist < check_distance:
            successorlane = admap.getLane(admap.getContactLanes(
                tlane, admap.ContactLocation(4))[0].toLane)
            sum_dist += float(successorlane.length)
            tlane = successorlane
            succ_lanes_list.append(tlane)
        return succ_lanes_list

    def find_back_lanes(self, car_pos, check_distance):
        succ_lanes_list = []
        sum_dist = 0
        car_pt = self.toENUPoint(car_pos)
        mapMatching = admap.AdMapMatching()
        car_map_matches = mapMatching.getMapMatchedPositions(
            car_pt, physics.Distance(10.0), physics.Probability(0.05))
        if not len(car_map_matches) > 0:
            return []
        # use nearest point
        car_pt_para = car_map_matches[0].lanePoint.paraPoint
        car_lane_id = car_pt_para.laneId
        car_laneoffset = car_pt_para.parametricOffset
        tlane = admap.getLane(car_lane_id)
        sum_dist += (1-float(car_laneoffset))*float(tlane.length)
        succ_lanes_list.append(tlane)
        while sum_dist < check_distance:
            successorlane = admap.getLane(admap.getContactLanes(
                tlane, admap.ContactLocation(5))[0].toLane)
            sum_dist += float(successorlane.length)
            tlane = successorlane
            succ_lanes_list.append(tlane)
        return succ_lanes_list

    def cal_relative_s(self, pos1, pos2):
        start_pt = self.toENUPoint(pos1)
        end_pt = self.toENUPoint(pos2)
        roads = self.GlobalPlanner(start_pt, end_pt)

        delta_s = 0
        for i, road in enumerate(roads):
            lanes = road.drivableLaneSegments
            current_lane = lanes[0]
            for lane in lanes:
                if lane.routeLaneOffset == 0:
                    current_lane = lane
                    break
            lane_interval = current_lane.laneInterval
            lane_id = current_lane.laneInterval.laneId
            lane_offset = current_lane.routeLaneOffset
            tlane = admap.getLane(lane_id)
            lane_length = float(tlane.length)
            tstart = current_lane.laneInterval.start
            tend = current_lane.laneInterval.end
            delta_s += float(tend-tstart)*lane_length

        return delta_s

    def find_front_cars(self, car_pos, vehicle_list, check_distance):
        choosen_idx = None
        try:
            candidiate_lanes = self.find_infront_lanes(car_pos, check_distance)
        except:
            candidiate_lanes = []
        front_cars_idxs = []
        for i in range(len(vehicle_list)):
            target_vehicle = vehicle_list[i]
            target_location = self.toENUPoint([target_vehicle.center.x,
                                               target_vehicle.center.y,
                                               target_vehicle.center.z])
            if target_location == None:
                continue

            try:
                mapMatching = admap.AdMapMatching()
                car_map_matches = mapMatching.getMapMatchedPositions(
                    target_location, physics.Distance(10.0), physics.Probability(0.05))
            except:
                car_map_matches = []

            if not len(car_map_matches) > 0:
                # print("error in find matching point"+str(target_location))
                continue
            car_pt_para = car_map_matches[0].lanePoint.paraPoint
            car_lane_id = car_pt_para.laneId
            for idx, lane in enumerate(candidiate_lanes):
                if car_lane_id == lane.id:
                    if idx != 0:
                        front_cars_idxs.append(i)
                    else:
                        car_pt = self.toENUPoint(car_pos)
                        mapMatching = admap.AdMapMatching()
                        car_map_matches = mapMatching.getMapMatchedPositions(
                            car_pt, physics.Distance(10.0), physics.Probability(0.05))
                        if car_map_matches[0].lanePoint.paraPoint.parametricOffset < car_pt_para.parametricOffset:
                            front_cars_idxs.append(i)
        min_dist = check_distance

        for i in front_cars_idxs:
            distance = math.sqrt(
                (vehicle_list[i].center.x-car_pos[0])**2+(vehicle_list[i].center.y-car_pos[1])**2)
            if distance < min_dist:
                min_dist = distance
                choosen_idx = i
        if choosen_idx is not None:
            return front_cars_idxs, choosen_idx
        else:
            return front_cars_idxs, None

    def cal_pcc_waypt(self, start_point, end_point, pcc_reader, total_distance, time_tick):
        global_plan = deque(maxlen=10000)
        speed_profile = deque(maxlen=10000)
        start_pt = self.toENUPoint(start_point)
        end_pt = self.toENUPoint(end_point)
        roads = self.GlobalPlanner(start_pt, end_pt)

        mapMatching = admap.AdMapMatching()
        car_map_matches = mapMatching.getMapMatchedPositions(
            start_pt, physics.Distance(10.0), physics.Probability(0.05))
        assert len(car_map_matches) > 0
        car_pt_para = car_map_matches[0].lanePoint.paraPoint
        car_laneoffset = car_pt_para.parametricOffset
        tstart_offset = car_laneoffset
        car_lane_id = car_pt_para.laneId
        tlane = admap.getLane(car_lane_id)
        tstart_offset = 0.0
        deltpara = 0.0
        tENUPoint = None
        for i, road in enumerate(roads):
            lanes = road.drivableLaneSegments
            current_lane = lanes[0]
            for lane in lanes:
                if lane.routeLaneOffset == 0:
                    current_lane = lane
                    break
            lane_interval = lane.laneInterval
            lane_id = lane.laneInterval.laneId
            lane_offset = lane.routeLaneOffset
            tlane = admap.getLane(lane_id)
            # if tlane.type is not "NORMAL":
            #     continue
            tstart = lane.laneInterval.start
            tend = lane.laneInterval.end
            tPara = tstart
            lane_length = float(tlane.length)
            tstart_offset = tstart_offset/lane_length
            distance = 0
            deltpara = deltpara/lane_length
            if i > 0 and tENUPoint is not None:
                matched_point = self.handle_lane_overlap(tlane, tENUPoint)
                tstart_offset += float(matched_point.paraPoint.parametricOffset)
            if tstart < tend:
                tPara = tstart + tstart_offset + deltpara
                while tPara <= tend:
                    tParaPoint = admap.createParaPoint(lane_id, tPara)
                    tENUPoint = admap.getENULanePoint(tParaPoint, 0.5)
                    if distance < total_distance:
                        x = float(tENUPoint.x)
                        y = float(tENUPoint.y)
                        z = float(tENUPoint.z)
                        # converted_ord = self.coord_trans.map_to_trucksim([x, y])
                        global_plan.append([x, y, z])
                        try:
                            v = float(pcc_reader.qurey_v(
                                pcc_reader.qurey_x(x, y)))
                        except:
                            v = float(pcc_reader.qurey_v(x, y))
                        if v == 0.0:
                            v = 16.67
                        speed_profile.append(v)
                        deltpara = (v*time_tick)/float(lane_length)
                        distance += v*time_tick
                    else:
                        return global_plan, speed_profile
                    tPara = tPara+deltpara
                    if tPara > tend:
                        deltpara = deltpara*lane_length
            else:
                tPara = tstart - tstart_offset - deltpara
                while tPara >= tend:
                    tParaPoint = admap.createParaPoint(lane_id, tPara)
                    tENUPoint = admap.getENULanePoint(tParaPoint, 0.5)
                    if distance < total_distance:
                        x = float(tENUPoint.x)
                        y = float(tENUPoint.y)
                        z = float(tENUPoint.z)
                        # converted_ord = self.coord_trans.map_to_trucksim([x, y])
                        global_plan.append([x, y, z])
                        try:
                            v = float(pcc_reader.qurey_v(
                                pcc_reader.qurey_x(x, y)))
                        except:
                            v = float(pcc_reader.qurey_v(x, y))
                        if v == 0.0:
                            v = 16.67
                        deltpara = (v*time_tick)/float(lane_length)
                        distance += v*time_tick
                        speed_profile.append(v)
                    else:
                        return global_plan, speed_profile
                    tPara = tPara-deltpara
                    if tPara < tend:
                        deltpara = deltpara*lane_length
        return global_plan, speed_profile

    def query_left_lane(self, waypoint):
        enu_point = self.toENUPoint(waypoint)
        mapMatching = admap.AdMapMatching()
        car_map_matches = mapMatching.getMapMatchedPositions(
            enu_point, physics.Distance(10.0), physics.Probability(0.05))
        if not len(car_map_matches) > 0:
            return None
        car_pt_para = car_map_matches[0].lanePoint.paraPoint
        car_laneoffset = car_pt_para.parametricOffset
        car_lane_id = car_pt_para.laneId
        tlane = admap.getLane(car_lane_id)
        try:
            left_lane = admap.getLane(admap.getContactLanes(
                tlane, admap.ContactLocation(2))[0].toLane)
        except:
            return None
        tParaPoint = admap.createParaPoint(left_lane.id, car_laneoffset)
        left_point = admap.getENULanePoint(tParaPoint, 0.5)
        return [float(left_point.x), float(left_point.y), float(left_point.z)]

    def query_right_lane(self, waypoint):
        enu_point = self.toENUPoint(waypoint)
        mapMatching = admap.AdMapMatching()
        car_map_matches = mapMatching.getMapMatchedPositions(
            enu_point, physics.Distance(10.0), physics.Probability(0.05))
        if not len(car_map_matches) > 0:
            return None
        car_pt_para = car_map_matches[0].lanePoint.paraPoint
        car_laneoffset = car_pt_para.parametricOffset
        tstart_offset = car_laneoffset
        car_lane_id = car_pt_para.laneId
        tlane = admap.getLane(car_lane_id)
        try:
            right_lane = admap.getLane(admap.getContactLanes(
                tlane, admap.ContactLocation(3))[0].toLane)
        except:
            return None
        tParaPoint = admap.createParaPoint(right_lane.id, car_laneoffset)
        right_lane = admap.getENULanePoint(tParaPoint, 0.5)
        return [float(right_lane.x), float(right_lane.y), float(right_lane.z)]

    def find_z(self, pos):
        pos_map = self.coord_trans.trucksim_to_map(pos)
        start_pt = self.toENUPoint(pos_map)

        mapMatching = admap.AdMapMatching()
        car_map_matches = mapMatching.getMapMatchedPositions(
            start_pt, physics.Distance(10.0), physics.Probability(0.05))
        if len(car_map_matches) <= 0:
            print("cannot find Z for location"+str(pos))
            return pos[2]
        #     print("invalid pos in find z"+str(pos))
        #     return pos[2]
        car_pt_para = car_map_matches[0].lanePoint.paraPoint
        tENUPoint = admap.getENULanePoint(car_pt_para, 0.5)
        trucksim_new_pos = self.coord_trans.map_to_trucksim(
            [float(tENUPoint.x), float(tENUPoint.y), float(tENUPoint.z)])
        return trucksim_new_pos[2]

    def find_z_map(self, pos):
        # pos  = self.coord_trans.trucksim_to_map(pos)
        start_pt = self.toENUPoint(pos)

        mapMatching = admap.AdMapMatching()
        car_map_matches = mapMatching.getMapMatchedPositions(
            start_pt, physics.Distance(10.0), physics.Probability(0.05))
        assert len(car_map_matches) > 0
        #     print("invalid pos in find z"+str(pos))
        #     return pos[2]
        car_pt_para = car_map_matches[0].lanePoint.paraPoint
        tENUPoint = admap.getENULanePoint(car_pt_para, 0.5)
        return float(tENUPoint.z)


class GlobalRouting():
    def __init__(self):
        pass


if __name__ == '__main__':
    MapServer()
    coord_trans = CoordTrans()

    start_pt = [-252.6831285, -6325.0292965, 297.536682]
    end_pt = [690.1756285, 6673.467041, 408.460602]

    lowest_point = [-563.393, -6133.13]

    start_pt_trucksim = coord_trans.map_to_trucksim(lowest_point)
    print(start_pt_trucksim)

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

    route_result = admap.planRoute(
        start_pt_para, end_pt_para, admap.RouteCreationMode.SameDrivingDirection)
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

        #print(lane_id, lane_offset)

        #pt = admap.getLaneParaPoint(physics.ParametricValue(1.0), lane.laneInterval)

        #print(admap.getLaneParaPoint(physics.ParametricValue(1), lane.laneInterval))

    # point::ParaPoint getLaneParaPoint(physics::ParametricValue const &routeParametricOffset,
    #                               route::LaneInterval const &laneInterval);

    print('done')

    # route::FullRoute routeResult = route::planning::planRoute(ENU2PARA(startPoint),ENU2PARA(endPoint),route::RouteCreationMode::Undefined);
    # route::RoadSegmentList roads = routeResult.roadSegments;
