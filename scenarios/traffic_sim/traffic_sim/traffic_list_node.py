#!/usr/bin/python3
#
# Copyright (c) 2020 Inceptio
#
from ad_map_server_py.ad_map_server import MapServer, CoordTrans
from trajectory_planner.HDMap import HDmap
from ament_index_python.packages import get_package_share_directory
from traffic_sim.preprocss import get_car_information
import time
import math
import os
import rclpy
from rclpy.node import Node


from fead_interfaces.msg import SimTick, Obstacle, PredictionResult, PerceptionResult, TrafficListMsg
from fead_interfaces.msg import VehicleModelOutput
from geometry_msgs.msg import Vector3
import std_msgs
import numpy as np

from collections import deque
#import pkg_resources

######################################
######################################
node_name = 'traffic_list'
pkg_name = 'traffic_sim'
node_share_dir = get_package_share_directory(pkg_name)

#traffic_sample_dir = os.path.join(node_share_dir, 'trafficData_mapped/twoLanes/sample4_selected')
traffic_sample_dir = os.path.join(
    node_share_dir, 'trafficData_mapped_angle/twoLanes/constantDistance/sample4')
#traffic_sample_dir = os.path.join(node_share_dir, 'trafficData_mapped/twoLanes/montage1')
# from trajectory_planner.coord_tranform import Coord_Trans
######################################
######################################


class TrafficAgent():
    def __init__(self, id, data_file):
        self.id = id
        self.data_file = data_file
        self.load_data()

    def load_data(self):
        self.x, self.y, self.z, self.lane_ids, self.yaw = get_car_information(
            self.data_file)
        assert len(self.x) == len(self.y)
        assert len(self.x) == len(self.z)
        assert len(self.x) == len(self.lane_ids)

        self.frame_num = len(self.x)
        self.pitch = [0.0] * self.frame_num
        #self.yaw = [0.0] * self.frame_num
        self.roll = [0.0] * self.frame_num

    def get(self, frame_id):
        frame_id = frame_id % self.frame_num
        return {'x': self.x[frame_id], 'y': self.y[frame_id], 'z': self.z[frame_id],
                'pitch': self.pitch[frame_id], 'yaw': self.yaw[frame_id],
                'roll': self.roll[frame_id], 'lane_ids': self.lane_ids[frame_id]}


class TrafficList(Node):
    def __init__(self):
        super().__init__(node_name)

        self._map = MapServer()
        self.prediction_length = 10

        self.pub_traffic_list = self.create_publisher(
            TrafficListMsg, 'TrafficListMsg', 10)
        self.subscription = self.create_subscription(SimTick, 'SimTick',
                                                     self.sim_tick_callback, 10)
        self.vehicle_subscription = self.create_subscription(VehicleModelOutput, 'VehicleModelOutput',
                                                             self.vehicle_callback, 10)
        self.subscription  # prevent unused variable warning
        self.vehicle_subscription

        timer_period = 1.0
        self.timer = self.create_timer(timer_period, self.timer_callback)

        self.black_list = []

        self.load_traffic_file(traffic_sample_dir)

        self.current_frame_id = 0

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

        self.check_dist_ahead = 1000.0

    def vehicle_callback(self, trucksim_output_msg):
        """
        Get the status of the ego car
        """
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

    def sim_tick_callback(self, msg):
        self.current_frame_id = int(msg.header.frame_id)

    def block_behind_cars(self, lane_list, agent, agent_id):

        data = agent.get(self.current_frame_id)
        lane_id = data['lane_ids']
        for tlane in lane_list:
            if lane_id == tlane.id:
                return
        # if this agent is not in visible range now
        for frame_id in range(self.current_frame_id+1, self.current_frame_id + self.prediction_length):
            data = agent.get(frame_id)

            # will go in to visible range in prediction length
            lane_id = data['lane_ids']
            for tlane in lane_list:
                if lane_id == tlane.id:
                    if not self.check_black_list(agent_id):
                        self.black_list.append(agent_id)

    def check_black_list(self, agent_id):
        for black_idx in self.black_list:
            if agent_id == black_idx:
                return True
        return False

    def check_agent_in_range(self, lane_list, agent):
        # for frame_id in range(self.current_frame_id, self.current_frame_id + self.prediction_length):
        data = agent.get(self.current_frame_id)

        lane_id = data['lane_ids']
        for tlane in lane_list:
            if lane_id == tlane.id:
                return True

        return False

    def select_traffic(self, check_dist):
        # return empty list
        selected_traffic_list = []
        # return selected_traffic_list

        if self.vehicle_state['ready'] == False:
            return selected_traffic_list

        ego_map = [self.vehicle_state['x'],
                   self.vehicle_state['y'], self.vehicle_state['z']]
        lane_list = self._map.find_front_neighbor_lanes(ego_map, check_dist)

        for vehicle_id in range(self.vehicle_num):
            # self.block_behind_cars(lane_list, self.agents[vehicle_id], vehicle_id)
            if self.check_agent_in_range(lane_list, self.agents[vehicle_id]) and not self.check_black_list(vehicle_id):
                selected_traffic_list.append(vehicle_id)
        return selected_traffic_list

    def timer_callback(self):
        select_list = self.select_traffic(self.check_dist_ahead)
        pub_msg = TrafficListMsg()
        for itm in select_list:
            pub_msg.traffic_list.append(itm)
        self.pub_traffic_list.publish(pub_msg)

    def load_traffic_file(self, traffic_sample_dir):
        info_file_path = os.path.join(traffic_sample_dir, 'info.txt')
        assert os.path.isfile(info_file_path)

        f_info = open(info_file_path, 'r')
        line = f_info.readline()
        line = line[:-1]
        self.vehicle_num = int(line.split(' ')[0])
        self.frame_num = int(line.split(' ')[2])

        self.agents = {}
        for vehicle_id in range(self.vehicle_num):
            data_file = os.path.join(
                traffic_sample_dir, str(vehicle_id) + '.txt')
            assert os.path.isfile(data_file)

            self.agents[vehicle_id] = TrafficAgent(vehicle_id, data_file)
            assert self.frame_num == self.agents[vehicle_id].frame_num

    # def check_frame_num(self):
    #     list = []
    #     for idx in range(self.vehicle_num):
    #         list.append(self.agents[idx].frame_num)
    #     print(list)
################## main entrance ######################


def main(args=None):
    rclpy.init(args=args)
    traffic_list_node = TrafficList()
    # traffic_list_node.check_frame_num()
    rclpy.spin(traffic_list_node)
    traffic_list_node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
