#!/usr/bin/python3
#
# Copyright (c) 2020 Inceptio
#
### Greedy lane Change Decision Maker
import math
import numpy as np
import pkg_resources
from collections import deque
import rclpy
from rclpy.node import Node
from std_msgs.msg import String

from ad_map_server_py.ad_map_server import MapServer, CoordTrans


from fead_interfaces.msg import LaneChangeMsgs
from fead_interfaces.msg import Obstacle, PredictionResult
from fead_interfaces.msg import VehicleModelOutput
from rl import RL_lc
from rl import *

from scipy.spatial import cKDTree as KDTree
import random

class TrafficProcessTest(Node):
    def __init__(self):
        super().__init__('traffic_process')
        self._map = MapServer()

        # self.coord_trans = CoordTrans()

        self.publisher = self.create_publisher(LaneChangeMsgs, 'LaneChangeMsgs', 10)
        ## min distance for lane change safty range, forward and backward

        self.highway_env_lane_width = 4
        self.fead_lane_width = 4
        self.highway_env_lc_dist = 1
        self.lc_dist = 100
        self.agent = RL_lc()
        # self.agent =  RLCalls()

        self.vehicle_state = {
            'x': 0.0,
            'y': 0.0,
            'z': 0.0,
            'pitch': 0.0,
            'yaw': 0.0,
            'roll': 0.0,
            'vx': 0.0,
            'vy': 0.0,
            'eng_trq_nm': 0.0,
            'eng_spd_rpm': 0.0,
            'gear_pos': 0.0,
            'ready': False,
            }

        self.subscription = self.create_subscription(
            PredictionResult,
            'PredictionResult',
            self.perception_callback,
            10)
        
        self.subscription_trucksim = self.create_subscription(
            VehicleModelOutput,
            'VehicleModelOutput',
            self.trucksim_output_callback,
            10)

        self.steps = 0

    def trucksim_output_callback(self, trucksim_output_msg):
        # update state
        self.vehicle_state['x'] = trucksim_output_msg.xo
        self.vehicle_state['y'] = trucksim_output_msg.yo
        self.vehicle_state['z'] = trucksim_output_msg.zo
        self.vehicle_state['pitch'] = trucksim_output_msg.pitch
        self.vehicle_state['yaw'] = trucksim_output_msg.yaw
        self.vehicle_state['roll'] = trucksim_output_msg.roll
        self.vehicle_state['vx'] = trucksim_output_msg.vx
        self.vehicle_state['vy'] = trucksim_output_msg.vy
        self.vehicle_state['eng_trq_nm'] = trucksim_output_msg.eng_trq_nm
        self.vehicle_state['eng_spd_rpm'] = trucksim_output_msg.eng_spd_rpm
        self.vehicle_state['gear_pos'] = trucksim_output_msg.gear_pos
        self.vehicle_state['ready'] = True
        
    def perception_callback(self, msg):
        if len(msg.frame)>0:
            vehicle_list = msg.frame[0].obstacles
        else:
            vehicle_list = []

        lanechangeop = LaneChangeMsgs()
        lanechangeop.header = msg.header

        if self.vehicle_state['ready'] == True:
            lc = self.run_step(vehicle_list)
            lanechangeop.lanechangeop = float(lc)

        else:
            lanechangeop.lanechangeop = float(0.0)

        self.publisher.publish(lanechangeop)

    def find_nearest_neighbor(self, ego_pos, vehicle_list, neighbor_num):
        neighbor_xyz = []
        neighbor_list = []
        for idx in range(len(vehicle_list)):
            neighbor_xyz.append([vehicle_list[idx].center.x, vehicle_list[idx].center.y, vehicle_list[idx].center.z])
        
        if len(vehicle_list) == 0:
            return 0, []
        kdtree = KDTree(neighbor_xyz)
        dist, ind = kdtree.query(ego_pos, k=neighbor_num)

        return dist, ind


    def convert_to_sl_data(self, ego_pos,ego_vx, ego_vy, neighbor):
        ## we assume that neighbor will always follow the lane, so vy = 0
        delta_vx = neighbor.speed - ego_vx 
        delta_vy = ego_vy
        
        neighbor_pos = [neighbor.center.x, neighbor.center.y, neighbor.center.z]

        if self._map.query_left_lane(ego_pos) is not None:
            if self._map.query_left_lane(neighbor_pos) is not None:
                delta_y = 0
            else:
                delta_y = -self.fead_lane_width
        else:
            if self._map.query_left_lane(neighbor_pos) is not None:
                delta_y = self.fead_lane_width
            else:
                delta_y = 0
        delta_x = self._map.cal_relative_s(ego_pos, neighbor_pos)
        return delta_x, delta_y, delta_vx, delta_vy

    def process_traffic(self, vehicle_list):
        def validate_traffic_list(input_list):
            del_list = []
            for i in range(len(input_list)):
                if input_list[i].center.x==0 and input_list[i].center.y==0 and input_list[i].center.z == 0:
                    del_list.append(i)
            for idx in range(len(del_list)):
                del input_list[del_list[len(del_list)-idx-1]]
            return input_list

        vehicle_list = validate_traffic_list(vehicle_list)
        v_idx = 0
        ## Sin theta 
        if self.last_planning_result is None:
            speed_array = np.zeros(5)
            for i in range(5):
                speed_array[i] = 19 + 4 * math.sin(1.0 / 3.0 * (self.step + i / 5)) + random.uniform(-0.2,0.2)

        ## pcc curve
        if self.last_planning_result is not None:
            speed_array = []
            for i in range(5):
                speed_array.append(self.last_planning_result.waypoints[i+1].speed)
            speed_array = np.array(speed_array)

        result_matrix = []

        ego_pos = [self.vehicle_state['x'],self.vehicle_state['y'],self.vehicle_state['z']]
        
        ## ego car information
        if self._map.query_left_lane(ego_pos) is not None:
            result_matrix.append([1, 1, 4, self.vehicle_state['vx'], 0.0, speed_array[v_idx]])
        else:
            result_matrix.append([1, 1, 0, self.vehicle_state['vx'], 0.0, speed_array[v_idx]])
        v_idx += 1

        ## neighbors' information
        if len(vehicle_list)>=4:
            neighbor_num = 4
        else:
            neighbor_num = len(vehicle_list)
        
        if len(vehicle_list) > 0:
            dist, ind = self.find_nearest_neighbor(ego_pos, vehicle_list, neighbor_num)

            if type(ind) == type(1):
                ind = [ind]
            for idx in ind:
                dx, dy, dvx, dvy = self.convert_to_sl_data(ego_pos, self.vehicle_state['vx'], self.vehicle_state['vy'], vehicle_list[idx])
                if dx > 100:
                    continue
                result_matrix.append([1, dx, dy, dvx, dvy, speed_array[v_idx]])
                v_idx += 1
        else:
            pass
        
        while len(result_matrix)<5:
            result_matrix.append([0, 0, 0, 0, 0, speed_array[v_idx]])
            v_idx += 1

        return result_matrix

    def lc_safty_check(self, lc_option, vehicle_list): 
        ego_vehicle_location = [self.vehicle_state['x'],self.vehicle_state['y'],self.vehicle_state['z']]
        ego_location_map = ego_vehicle_location
        lane_list = self._map.find_lc_lanes(ego_location_map, lc_option, self.lane_change_detection)
        
        for vehicle in vehicle_list:
            try:
                lane_id = self._map.find_lane_id([vehicle.center.x, vehicle.center.y, vehicle.center.z])
            except:
                continue
            for tlane in lane_list:
                if lane_id == tlane.id:
                    return True
        return True

    def run_rl_network(self, matrix):
        ## run rl here
        action = self.agent.lanechange(np.array(matrix))[0]
        print(self.agent.lanechange(np.array(matrix)))
        if action ==3 or action == 4:
            action = 1
        return action-1

    def run_step(self, vehicle_list):
        
        input_matrix = self.process_traffic(vehicle_list)
        lc = self.run_rl_network(input_matrix)

        return lc

    def virtual_test(self, input_matrix):
        lc = self.run_rl_network(input_matrix)

################## main entrance ######################
def main(args=None):
    rclpy.init(args=args)
    traffic_process = TrafficProcessTest()
    input_matrix=[[ 1.00000000e+00 , 1.00000000e+00 , 5.00000000e-01 , 4.75607908e-01,
            0.00000000e+00, 0.5],
            [ 1.00000000e+00  ,6.80511226e-03  ,0.00000000e+00 ,-2.64913562e-01,
            4.72061434e-04,0.5],
            [ 0.00000000e+00 , 0.00000000e+00 , 0.00000000e+00,  0.00000000e+00,
            0.00000000e+00,0.5],
            [ 0.00000000e+00 , 0.00000000e+00 , 0.00000000e+00 , 0.00000000e+00,
            0.00000000e+00,0.5],
            [ 0.00000000e+00 , 0.00000000e+00 , 0.00000000e+00,  0.00000000e+00,
            0.00000000e+00,0.5]]

    rclpy.spin(traffic_process)
    traffic_process.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()