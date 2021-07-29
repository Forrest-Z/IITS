#!/usr/bin/python3
#
# Copyright (c) 2020 Inceptio
#
from collections import deque

import sys
import os

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

import rclpy
from rclpy.node import Node
import math
import numpy as np

from trajectory_planner.coord_tranform import Coord_Trans

from fead_interfaces.srv._access_lane_id import *
from fead_interfaces.srv._access_left_lane import *
from fead_interfaces.srv._access_right_lane import *
from fead_interfaces.srv._routing import *
from fead_interfaces.srv._get_z import *

class HDmap(Node):
    def __init__(self, \
        map_dir=os.path.join(resource_dir, 'jinan_two_lanes_config.txt')):
        super().__init__('HDmap')
        self.node = self
        self.map_dir = map_dir
        admap.init(self.map_dir)
        self.coord_trans = Coord_Trans(-225.151904, -6337.384475)
        self.routing_result = None
        self.req_lane_id = self._create_client(AccessLaneID, 'AccessLaneID')
        self.req_left_lane = self._create_client(AccessLeftLane, 'AccessLeftLane')
        self.req_right_lane = self._create_client(AccessRightLane, 'AccessRightLane')
        self.req_routing = self._create_client(Routing, 'Routing')
        self.req_Z = self._create_client(GetZ, 'GetZ')

    def _create_client(self, service_tocall, service_name):
        service = self.node.create_client(service_tocall, service_name)
        while not service.wait_for_service(timeout_sec=0.1):
            self.node.get_logger().info('service '+service_name+ ' not available, waiting again...')
        self.node.get_logger().info('connected to service '+service_name)
        return service

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

    def find_lc_lanes(self,car_pos, lc_op, check_dist):
        succ_lanes_list = self.find_infront_lanes(car_pos, check_dist)
        lc_lanes = []
        for tlane in succ_lanes_list:
            try:
                if lc_op == -1: ## left
                    left_lane = admap.getLane(admap.getContactLanes(tlane, admap.ContactLocation(2))[0].toLane)
                    lc_lanes.append(left_lane)
                elif lc_op == 1: ## right
                    right_lane = admap.getLane(admap.getContactLanes(tlane, admap.ContactLocation(3))[0].toLane)
                    lc_lanes.append(right_lane)
                else:
                    pass
            except:
                pass
        
        return lc_lanes

    def find_front_neighbor_lanes(self, car_pos, check_dist):
        candidiate_list = []
        succ_lanes_list = self.find_infront_lanes(car_pos, check_dist)
        for tlane in succ_lanes_list:
            try:
                left_lane = admap.getLane(admap.getContactLanes(tlane, admap.ContactLocation(2))[0].toLane)
                candidiate_list.append(left_lane)
            except:
                pass
            try:
                right_lane = admap.getLane(admap.getContactLanes(tlane, admap.ContactLocation(3))[0].toLane)
                candidiate_list.append(right_lane)
            except:
                pass
            candidiate_list.append(tlane)
        return candidiate_list

    def handle_lane_overlap(self, target_lane, previous_end_point):
        ecef_point = admap.toECEF(previous_end_point)
        result = admap.MapMatchedPosition()
        result_flag = admap.findNearestPointOnLane(target_lane, ecef_point, result)
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
        tstart_offset = 0.0
        for i,road in enumerate(roads):
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
            if i>0 and tENUPoint is not None:
                matched_point = self.handle_lane_overlap(tlane, tENUPoint)
                tstart_offset += float(matched_point.paraPoint.parametricOffset)
            if tstart<tend:
                tPara = tstart + tstart_offset+deltpara
                while tPara<=tend:
                    tParaPoint = admap.createParaPoint(lane_id, tPara)
                    tENUPoint = admap.getENULanePoint(tParaPoint, 0.5)
                    if len(global_plan)<num_waypt:
                        x = float(tENUPoint.x)
                        y = float(tENUPoint.y)
                        z = float(tENUPoint.z)
                        converted_ord = self.coord_trans.map_to_trucksim(x, y)
                        global_plan.append([converted_ord[0],converted_ord[1],z])
                    else:
                        return global_plan
                    tPara = tPara+deltpara
            else:
                tPara = tstart - tstart_offset - deltpara
                while tPara>=tend:
                    tParaPoint = admap.createParaPoint(lane_id, tPara)
                    tENUPoint = admap.getENULanePoint(tParaPoint,0.5)
                    if len(global_plan)<num_waypt:
                        x = float(tENUPoint.x)
                        y = float(tENUPoint.y)
                        z = float(tENUPoint.z)
                        converted_ord = self.coord_trans.map_to_trucksim(x, y)
                        global_plan.append([converted_ord[0],converted_ord[1],z])
                    else:
                        return global_plan
                    tPara = tPara-deltpara
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
            successorlane = admap.getLane(admap.getContactLanes(tlane, admap.ContactLocation(4))[0].toLane)
            sum_dist += float(successorlane.length)
            tlane = successorlane
            succ_lanes_list.append(tlane)
        return succ_lanes_list
    
    def find_front_cars(self, car_pos, vehicle_list, check_distance):
        choosen_idx = None
        candidiate_lanes = self.find_infront_lanes(car_pos, check_distance)
        front_cars_idxs = []
        for i in range(len(vehicle_list)):
            target_vehicle = vehicle_list[i]
            target_location = self.toENUPoint([target_vehicle.center.x, \
                                            target_vehicle.center.y,\
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
                continue
            car_pt_para = car_map_matches[0].lanePoint.paraPoint
            car_lane_id = car_pt_para.laneId
            for lane in candidiate_lanes:
                if car_lane_id == lane.id:
                    front_cars_idxs.append(i)
        min_dist = check_distance
        
        for i in front_cars_idxs:
            distance = math.sqrt((vehicle_list[i].center.x-car_pos[0])**2+(vehicle_list[i].center.y-car_pos[1])**2)
            if distance<min_dist:
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
        for i,road in enumerate(roads):
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
            tstart = lane.laneInterval.start
            tend = lane.laneInterval.end
            tPara = tstart;
            lane_length = float(tlane.length)
            tstart_offset = tstart_offset/lane_length
            distance = 0
            deltpara = deltpara/lane_length
            if i>0 and tENUPoint is not None:
                matched_point = self.handle_lane_overlap(tlane, tENUPoint)
                tstart_offset += float(matched_point.paraPoint.parametricOffset)
            if tstart<tend:
                tPara = tstart + tstart_offset + deltpara
                while tPara<=tend:
                    tParaPoint = admap.createParaPoint(lane_id, tPara)
                    tENUPoint = admap.getENULanePoint(tParaPoint, 0.5)
                    if distance<total_distance:
                        x = float(tENUPoint.x)
                        y = float(tENUPoint.y)
                        z = float(tENUPoint.z)
                        converted_ord = self.coord_trans.map_to_trucksim(x, y)
                        global_plan.append([converted_ord[0],converted_ord[1],z])
                        try:
                            v = float(pcc_reader.qurey_v(pcc_reader.qurey_x(converted_ord[0],converted_ord[1])))
                        except:
                            v = float(pcc_reader.qurey_v(converted_ord[0],converted_ord[1]))
                        if v == 0.0:
                            v = 5.0
                        speed_profile.append(v)
                        deltpara = (v*time_tick)/float(lane_length)
                        distance += v*time_tick
                    else:
                        return global_plan, speed_profile
                    tPara = tPara+deltpara
                    if tPara>tend:
                        deltpara = deltpara*lane_length
            else:
                tPara = tstart - tstart_offset -deltpara
                while tPara>=tend:
                    tParaPoint = admap.createParaPoint(lane_id, tPara)
                    tENUPoint = admap.getENULanePoint(tParaPoint,0.5)
                    if distance<total_distance:
                        x = float(tENUPoint.x)
                        y = float(tENUPoint.y)
                        z = float(tENUPoint.z)
                        converted_ord = self.coord_trans.map_to_trucksim(x, y)
                        global_plan.append([converted_ord[0],converted_ord[1],z])
                        try:
                            v = float(pcc_reader.qurey_v(pcc_reader.qurey_x(converted_ord[0],converted_ord[1])))
                        except:
                            v = float(pcc_reader.qurey_v(converted_ord[0],converted_ord[1]))
                        deltpara = (v*time_tick)/float(lane_length)
                        distance += v*time_tick
                        speed_profile.append(v)
                    else:
                        return global_plan, speed_profile
                    tPara = tPara-deltpara
                    if tPara < tend:
                        deltpara = deltpara*lane_length
        return global_plan, speed_profile

    def _calc_relative_x_h(self, waypoint_buffer):
        def calc_distance(x1,y1,x2,y2):
            return math.sqrt((x1-x2)**2+(y1-y2)**2)
        x = [0]
        grad = [waypoint_buffer[0][2]]
        for i in range(len(waypoint_buffer)-1):
            x.append(x[i]+calc_distance(waypoint_buffer[i][0], waypoint_buffer[i][1], waypoint_buffer[i+1][0], waypoint_buffer[i+1][1]))
            grad.append(waypoint_buffer[i+1][2])
        return x, grad

    def GlobalPlanner_waypoints(self, start_pos, end_pos):
        global_plan = deque(maxlen=1000000000000000000)
        req = Routing_Request()
        req.begin_pos.x = start_pos[0]
        req.begin_pos.y = start_pos[1]
        req.begin_pos.z = start_pos[2]
        req.end_pos.x = end_pos[0]
        req.end_pos.y = end_pos[1]
        req.end_pos.z = end_pos[2]
        result = self.req_routing.call_async(req)
        rclpy.spin_until_future_complete(self.node, result)
        if result.result() is not None:
            for waypoint in result.result().waypoints:
                converted_ord = self.coord_trans.map_to_trucksim(waypoint.x, waypoint.y)
                global_plan.append([converted_ord[0], converted_ord[1], waypoint.z])
            print("succ GP, len"+str(len(global_plan)))
            return global_plan
        else:
            self.node.get_logger().error('Exception while calling service GP: %r' % result.exception())
            return None

    def query_left_lane(self, waypoint):
        req = AccessLeftLane_Request()
        req.waypoint.x = waypoint[0]
        req.waypoint.y = waypoint[1]
        req.waypoint.z = waypoint[2]
        result = self.req_left_lane.call_async(req)
        rclpy.spin_until_future_complete(self.node, result, timeout_sec=0.1)
        if result.result() is not None:
            if result.result().flag == True:
                converted_ord = self.coord_trans.map_to_trucksim(result.result().waypoint.x, result.result().waypoint.y)
                return [converted_ord[0],converted_ord[1],result.result().waypoint.z]  
            else:
                return None
        else:
            self.node.get_logger().error('Exception while calling service left lane: %r' % result.exception())
            print(str(req.waypoint))
            return None

    def query_z(self, x, y):
        req = GetZ_Request()
        req.x = x
        req.y = y
        result = self.req_Z.call_async(req)
        rclpy.spin_until_future_complete(self.node, result, timeout_sec = 1)
        if result.result() is not None:
            if result.result().lane_id == 0:
                print("error returned from MAP server, x="+str(x)+"y = "+str(y))
                return 0
            else:
                return result.result().z
        else:
            self.node.get_logger().error('Exception while calling service get Z: %r' % result.exception())
            return 0


    def query_right_lane(self, waypoint):
        req = AccessRightLane_Request()
        req.waypoint.x = waypoint[0]
        req.waypoint.y = waypoint[1]
        req.waypoint.z = waypoint[2]
        result = self.req_right_lane.call_async(req)
        rclpy.spin_until_future_complete(self.node, result, timeout_sec=0.1)
        if result.result() is not None:
            if result.result().flag == True:
                converted_ord = self.coord_trans.map_to_trucksim(result.result().waypoint.x, result.result().waypoint.y)
                return [converted_ord[0],converted_ord[1],result.result().waypoint.z]  
            else:
                return None
        else:
            self.node.get_logger().error('Exception while calling service right lane: %r' % result.exception())
            print(str(req.waypoint))
            return None
    
    def query_lane_road_id(self, location):
        req = AccessLaneID_Request()
        req.waypoint.x = location[0]
        req.waypoint.y = location[1]
        req.waypoint.z = location[2]
        result = self.req_lane_id.call_async(req)
        rclpy.spin_until_future_complete(self.node, result, timeout_sec=0.1)
        if result.result() is not None:
            return result.result().lane_id
        else:
            self.node.get_logger().error('Exception while calling service lane id: %r' % result.exception())
            print(str(req.waypoint))
            return None
    
    def query_gradient(self, waypoint_buffer):
        x, grad = self._calc_relative_x_h(waypoint_buffer)
        return x, grad

def main(args=None):
    rclpy.init(args=args)
    map = HDmap()
    list = map.find_front_neighbor_lanes([-834.719,-5942.98,299.722],1000)
    print(list)

if __name__ == '__main__':
    main()