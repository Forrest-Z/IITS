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

from trajectory_planner.HDMap import HDmap
from ad_map_server_py.ad_map_server import MapServer, CoordTrans


from fead_interfaces.msg import LaneChangeMsgs
from fead_interfaces.msg import Obstacle, PredictionResult
from fead_interfaces.msg import VehicleModelOutput
# from trajectory_planner.coord_tranform import Coord_Trans
from trajectory_planner.offline_pcc import PCCReader

class Greedy_Lane_Change(Node):
    def __init__(self, start_point, end_point):
        super().__init__('greedy_dm')
        self._map = MapServer()

        self.max_step = 1000
        self.global_timer = 0
        self.done = False

        self.publisher = self.create_publisher(LaneChangeMsgs, 'LaneChangeMsgs', 10)
        ## min distance for lane change safty range, forward and backward
        self.lane_change_detection = 100.0 

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
        self.done = False

        if len(msg.frame)>0:
            vehicle_list = msg.frame[0].obstacles
        else:
            vehicle_list = []

        lanechangeop = LaneChangeMsgs()
        lanechangeop.header = msg.header

        if self.global_timer == self.max_step:
            self.done = True

        if self.vehicle_state['ready'] == True:
            propose_lane_change = self._is_vehicle_hazard(vehicle_list)
            lc = self.run_step(propose_lane_change, vehicle_list)
            lanechangeop.lanechangeop = float(lc)
            lanechangeop.done = self.done

        else:
            lanechangeop.lanechangeop = float(0.0)
            lanechangeop.done = self.done

        if self.done:

            self.global_timer = 0

        self.global_timer += 1
        self.publisher.publish(lanechangeop)

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
                
    def simple_lane_change(self, vehicle_list):
    ## -1 =left 0=keep 1=right
        ego_vehicle_location = [self.vehicle_state['x'],self.vehicle_state['y'],self.vehicle_state['z']]
        ego_location_map = ego_vehicle_location

        if len(self._map.find_lc_lanes(ego_location_map,-1,self.lane_change_detection))>0 \
            and self.lc_safty_check(-1,vehicle_list):
            print('change left')
            return -1
        elif len(self._map.find_lc_lanes(ego_location_map,1,self.lane_change_detection))>0\
             and self.lc_safty_check(1,vehicle_list):
            print('change right')
            return 1
        else:
            return 0

    def _is_vehicle_hazard(self, vehicle_list):
        ego_vehicle_location = [self.vehicle_state['x'],self.vehicle_state['y'],self.vehicle_state['z']]
        ego_location_map = ego_vehicle_location
   
        _, choosen_idx = self._map.find_front_cars(ego_location_map, vehicle_list, self.lane_change_detection)
        
        if choosen_idx is not None:
            return True
        else:
            return False

    def run_step(self, propose_lane_change, vehicle_list):

        if propose_lane_change:
            lc = self.simple_lane_change(vehicle_list)
        else:
            lc = 0
        return lc

################## main entrance ######################
def main(args=None):
    rclpy.init(args=args)
    greedy_dm_node = Greedy_Lane_Change([-112.0-2.114085999999986, 76.4-3.2139649999999165,296.0696],[927.53599-2.114085999999986, 12948.4684-3.2139649999999165, 408.727])
    rclpy.spin(greedy_dm_node)
    greedy_dm_node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()