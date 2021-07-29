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
import random
import time

from ad_map_server_py.ad_map_server import MapServer, CoordTrans

from fead_interfaces.msg import PlanningResult 
from fead_interfaces.msg import LaneChangeMsgs
from fead_interfaces.msg import Obstacle, PredictionResult
from fead_interfaces.msg import VehicleModelOutput

try:
    from rl_ros import RL_lc
    from utils import lmap
except:
    from rl_decision_making.rl_ros import RL_lc
    from rl_decision_making.utils import lmap

from scipy.spatial import cKDTree as KDTree
from trajectory_planner.offline_pcc import PCCReader2, PCCReader

class TrafficProcessTest(Node):
    def __init__(self):
        super().__init__('traffic_process')
        self._map = MapServer()

        self.publisher = self.create_publisher(LaneChangeMsgs, 'LaneChangeMsgs', 10)
        ## min distance for lane change safty range, forward and backward

        self.highway_env_lane_width = 4
        self.fead_lane_width = 4
        self.highway_env_lc_dist = 1
        self.lc_dist = 100
        self.agent = RL_lc(train=False, recover=True)
        self.pre_observation = None
        self.observation = None
        self.step = 0
        self.global_timer = 0
        self.max_step = 600
        self.done = False
        self.num_episodes = 10000
        self.episode = 0
        self.rewards = []
        self.speed_errors = []
        self.loss = []
        self.reward = 0
        self.action = None
        self.pre_action =None
        self.info = None
        self.pcc_reader = PCCReader2()
        self.use_history = True
        if self.use_history == False:
            self.agent.use_histroy = True
            self.agent.set_mode()

        self.last_planning_result = None
        self.no_vehicle_ob = False
        self.no_vehicle_ob_last_time = False

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

        self.sub_planning_result = self.create_subscription(
            PlanningResult,
            "planning_result",
            self.planner_result_callback,
            10
        )

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
    
    def planner_result_callback(self, msg):
        self.last_planning_result = msg

    def perception_callback(self, msg):
        self.no_vehicle_ob = True
        time_begin = time.time()
        self.done = False

        if len(msg.frame)>0:
            vehicle_list = msg.frame[0].obstacles
        else:
            vehicle_list = []

        lanechangeop = LaneChangeMsgs()
        lanechangeop.header = msg.header

        if self.vehicle_state['ready'] == True:
            self.observation = self.process_traffic(vehicle_list)
            if self.use_history:
                try:
                    curr_obs,pre_obs = self.agent.store_history(self.agent.normalize_obs(self.observation))
                except:
                    print("does not store history observation")
                self.action = self.agent.get_action(curr_obs)
            else:
                self.action = self.agent.get_action(self.agent.normalize_obs(self.observation))
        
            lanechangeop.lanechangeop = float(self.action-1)  
        else:
            lanechangeop.lanechangeop = float(0.0)

        if self.global_timer == self.max_step:
            self.done = True
        if self.vehicle_state['y']> 6000:
            self.done = True

        if not self.no_vehicle_ob_last_time:
            self.step += 1
            if self.pre_observation is not None:
                self.reward, speed_error = self.get_reward(self.action, self.observation)
                self.rewards.append(self.reward)
                self.speed_errors.append(speed_error)
                self.info = self.get_info()

                if self.use_history:
                    loss = self.agent.record(pre_obs,self.pre_action,self.reward,curr_obs,self.done,self.info)
                else:
                    loss = self.agent.record(self.agent.normalize_obs(self.pre_observation), self.pre_action,self.reward,self.agent.normalize_obs(self.observation),self.done,self.info)
                if loss is not None:

                    self.loss.append(loss)

        if self.done:
            self.episode += 1
            if self.step > 0:
                self.agent.after_all_episodes(self.episode,self.rewards, self.speed_errors, self.loss, self.step)
                self.agent.after_some_episodes(self.episode,self.rewards)
            self.rewards = []
            self.loss = []
            self.speed_errors = []
            self.step = 0
            self.global_timer = 0
            
        self.global_timer += 1
        self.pre_observation = self.observation
        self.no_vehicle_ob_last_time = self.no_vehicle_ob
        self.pre_action = self.action
        lanechangeop.done = self.done
        if self.no_vehicle_ob:
            lanechangeop.lanechangeop = float(0.0)
        self.publisher.publish(lanechangeop)

        if self.episode == self.num_episodes:
            self.agent.close()
        print("DM  FPS:"+str(1/(time.time()-time_begin)))

    def find_nearest_neighbor(self, ego_pos, vehicle_list, neighbor_num):
        neighbor_xyz = []
        neighbor_list = []
        for idx in range(len(vehicle_list)):
            neighbor_xyz.append([vehicle_list[idx].center.x, vehicle_list[idx].center.y, vehicle_list[idx].center.z])
        kdtree = KDTree(neighbor_xyz)
        dist, ind = kdtree.query(ego_pos, k=neighbor_num)

        return dist, ind

    def whether_back_me(self, vehicle_location, vehicle_rotation, neighbor_pos):
        v_begin = np.array(vehicle_location)
        v_end = v_begin + np.array([math.cos(math.radians(vehicle_rotation)),
                                        math.sin(math.radians(vehicle_rotation)),0])
        v_vec = np.array([v_end[0] - v_begin[0], v_end[1] - v_begin[1], 0.0])
        w_vec = np.array([neighbor_pos[0] -
                        v_begin[0], neighbor_pos[1] -
                        v_begin[1], 0.0])
        if np.clip(np.dot(w_vec, v_vec) /
                                (np.linalg.norm(w_vec) * np.linalg.norm(v_vec)), -1.0, 1.0)< 0:
                                return True
        return False

    def convert_to_sl_data(self, ego_pos,ego_vx, ego_vy, neighbor, front_or_back):
        ## we assume that neighbor will always follow the lane, so vy = 0
        delta_vx = ego_vx - neighbor.speed
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
        if front_or_back == "front":
            delta_x = self._map.cal_relative_s(ego_pos, neighbor_pos)
        else:
            delta_x = -self._map.cal_relative_s(neighbor_pos, ego_pos)
        return delta_x, delta_y, delta_vx, delta_vy

    def process_traffic(self, vehicle_list):
        def validate_traffic_list(input_list):
            del_list = []
            for i in range(len(input_list)):
                if input_list[i].center.x==0 or input_list[i].center.y==0 or input_list[i].center.z == 0:
                    del_list.append(i)
            for idx in range(len(del_list)):
                del input_list[del_list[len(del_list)-idx-1]]
            return input_list

        vehicle_list = validate_traffic_list(vehicle_list)
        v_idx = 0

        ## for offline pcc curve
        speed_array = []
        vehicle_pos = [self.vehicle_state['x'],self.vehicle_state['y']] 
        target_speed = self.query_optimal_speed(vehicle_pos)
        for i in range(9):
            speed_array.append(target_speed)
        speed_array = np.array(speed_array)

        result_matrix = []
        ego_pos = [self.vehicle_state['x'],self.vehicle_state['y'],self.vehicle_state['z']]
        
        ## ego car information
        if self._map.query_left_lane(ego_pos) is not None:
            result_matrix.append([1, 1, 4, self.vehicle_state['vx'], 0.0, speed_array[v_idx]])
        else:
            result_matrix.append([1, 1, 0, self.vehicle_state['vx'], 0.0, speed_array[v_idx]])
        v_idx += 1

        if len(vehicle_list) == 0:
            while len(result_matrix)<9:
                result_matrix.append([0, 0, 0, 0, 0, speed_array[v_idx]])
                v_idx += 1
            return result_matrix

        dist, ind = self.find_nearest_neighbor(ego_pos, vehicle_list, len(vehicle_list))
        if type(ind) == type(1):
            ind = [ind]
        valid_back_neighbor = 0
        ## back neighbor information
        for idx in ind:
            if self.whether_back_me(ego_pos, self.vehicle_state['yaw'], [vehicle_list[idx].center.x,vehicle_list[idx].center.y, vehicle_list[idx].center.z]) and len(result_matrix)<3:
                dx, dy, dvx, dvy = self.convert_to_sl_data(ego_pos, self.vehicle_state['vx'], self.vehicle_state['vy'], vehicle_list[idx], "back")
                if dx <-50:
                    continue
                result_matrix.append([1, dx, dy, dvx, dvy, speed_array[v_idx]])
                valid_back_neighbor += 1
                v_idx += 1
        while len(result_matrix)<3:
            result_matrix.append([0, 0, 0, 0, 0, speed_array[v_idx]])
            v_idx += 1

        ## front neighbors' information
        valid_front_neighbor = 0
        for idx in ind:
            if not self.whether_back_me(ego_pos, self.vehicle_state['yaw'], [vehicle_list[idx].center.x,vehicle_list[idx].center.y, vehicle_list[idx].center.z]) and len(result_matrix)<9: 
                dx, dy, dvx, dvy = self.convert_to_sl_data(ego_pos, self.vehicle_state['vx'], self.vehicle_state['vy'], vehicle_list[idx], "front")
                if dx > 100:
                    continue
                result_matrix.append([1, dx, dy, dvx, dvy, speed_array[v_idx]])
                v_idx += 1
                valid_front_neighbor += 1
        
        while len(result_matrix)<9:
            result_matrix.append([0, 0, 0, 0, 0, speed_array[v_idx]])
            v_idx += 1

        print("front neighbor num:"+str(valid_front_neighbor)+" back neighbor num:"+str(valid_back_neighbor))

        for i in range(1,len(result_matrix)):
            if result_matrix[i][0] != 0:
                self.no_vehicle_ob = False

        return result_matrix

    def query_optimal_speed(self, current_pos):
        ## for offline query pcc
        v = float(self.pcc_reader.qurey_v(current_pos[0], current_pos[1])) 
        
        if v == 0.0:
            v = 16.67
        return v

    def check_lc_danger(self, obs):
        for row in range(len(obs)):
            if row == 0:
                continue
            if abs(obs[row][1]) < 10 and abs(obs[row][0])!=0 and obs[row][2]!=0:
                return True
 
        return False
    
    def get_reward(self, action, observation):
        vehicle_pos = [self.vehicle_state['x'],self.vehicle_state['y']] 
        target_speed = self.query_optimal_speed(vehicle_pos)
        speed_error = lmap(abs(self.vehicle_state['vx'] - target_speed),[0,20],[1,0])
        if action != 1:
            if self.check_lc_danger(observation):
                lane_change = -20.0
                print("danger lane change!")
            else:
                lane_change = -10
        else:
            lane_change = 0.0
        
        return speed_error + lane_change, speed_error

    def get_info(self):
        return {"dd":11}

################## main entrance ######################
def main(args=None):
    rclpy.init(args=args)
    traffic_process = TrafficProcessTest()
    rclpy.spin(traffic_process)
    traffic_process.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()