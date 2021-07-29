#!/usr/bin/python3
#
# Copyright (c) 2020 Inceptio
#
"""
Class that handle communication between CARLA and ROS
"""
import queue

import os, sys
import random, datetime, math, re, weakref
import logging, collections, argparse
import numpy as np

from distutils.version import LooseVersion
from threading import Thread, Lock, Event
import pkg_resources
import rclpy
from rclpy.node import Node
import time

import pygame
import carla

try:
    from carla_wrapper import World, HUD, KeyboardControl
except ImportError as error:
    from carla_bridge.carla_wrapper import World, HUD, KeyboardControl

#from ad_map_server_py.ad_map_server import MapServer, CoordTrans
from fead_interfaces.msg import LaneChangeMsgs
from fead_interfaces.msg import VehicleModelOutput, VehicleModelInput
from fead_interfaces.msg import Obstacle, PredictionResult, PerceptionResult
from fead_interfaces.msg import PlanningResult 
from collections import deque
from scipy.spatial.transform import Rotation, Slerp

# ==============================================================================
# -- CarlaBridge ---------------------------------------------------------------
# ==============================================================================

def carla_transform_numpy(trans):
    t = trans.location
    r = trans.rotation
    t_np = np.array([t.x, t.y, t.z])
    r_np = Rotation.from_euler('xyz', [r.pitch, r.yaw, r.roll])
    return t_np, r_np

def numpy_transform_carla(t, r):
    r_eular = r.as_euler('xyz')
    return carla.Transform(carla.Location(t[0], t[1], t[2]), 
        carla.Rotation(r_eular[0], r_eular[1], r_eular[2]))

def slerp_tranform(t0, r0, t1, r1, interp_num):
    t_interp = np.linspace(t0, t1, interp_num + 1)

    # stack together
    r01 = Rotation.from_quat(np.stack([r0.as_quat(), r1.as_quat()]))
    slerp = Slerp([0, interp_num], r01)
    r_interp = slerp(np.linspace(0, interp_num, interp_num + 1))
    
    return t_interp, r_interp

# t0 = [1.0, 2.0, 3.0]
# t1 = [100.0, 100.0, 100.0]
# r0 = Rotation.random(1)
# r1 = Rotation.random(1)
# tt, rr = slerp_tranform(t0, r0, t1, r1, 5)
# print(tt)
# print(rr.as_euler('xyz'))

class TrafficAgent():
    def __init__(self, carla_actor, id = -1, carla_world = None):
        self.id = id
        #self.transforms = []
        #self.frames = []
        self.carla_actor = carla_actor
        self.carla_world = carla_world
        #self.current_frame = -1
        self.last_trans = None

        self.display_buffer_size = 100
        self.display_deque = deque(maxlen=self.display_buffer_size)
        self.frame_id = 0
        
    def update_input(self, frame_id, trans, interp_num = 1.0):
        self.frame_id = frame_id
        #self.frames.append(frame_id)
        #self.transforms.append(trans)
        self.display_deque.append(trans)

        # the fist time
        # if self.last_trans == None:
        #     self.last_trans = trans
        #     self.display_deque.append(trans)
        #     return 

        # interp_num = int(round(interp_num)+1)

        # exist_num = len(self.display_deque)
        # # if exist_num >= interp_num - 1:
        # #     extra_interp_num = 0
        # # else:

        # extra_interp_num = interp_num - exist_num
        # if extra_interp_num <= 1:
        #     self.display_deque.append(trans)
        # else:
        #     t_last, r_last = carla_transform_numpy(self.last_trans)
        #     t_now, r_now = carla_transform_numpy(trans)
        #     t_interp, r_interp = slerp_tranform(t_last, r_last, t_now, r_now, extra_interp_num)
        #     for idx in range(1, extra_interp_num+1, 1):
        #         t_carla = numpy_transform_carla(t_interp[idx], r_interp[idx])
        #         self.display_deque.append(t_carla)

        # # update last trans
        # self.last_trans = trans

    def update_display(self):
        try:
            trans = self.display_deque.popleft()
            self.carla_actor.set_transform(trans)

            # update display
            loc = trans.location
            loc.z += 3.0
            self.carla_world.debug.draw_string(loc, text=str(self.id), life_time=0.5)
        except IndexError as error:
            # do not update display
            pass

class TrafficAgentManager():
    def __init__(self, world):
        self.agents = {}
        self.world = world
        self.spwan_points = self.world.get_map().get_spawn_points()
        
    def update_input(self, agent_id, frame_id, trans, interp_num = 1.0):
        if agent_id not in self.agents:
            # spawn an carla actor
            bp_vehicleAll = self.world.get_blueprint_library().filter('vehicle.*')
            bp_choosed = [x for x in bp_vehicleAll if int(x.get_attribute('number_of_wheels'))==4]
            bp_vehicle = random.choice(bp_choosed)
            if bp_vehicle.has_attribute('color'):
                color = random.choice(bp_vehicle.get_attribute('color').recommended_values)
                bp_vehicle.set_attribute('color', color)
            
            point = random.choice(self.spwan_points)
            # TODO : 
            #point.location.z += (agent_id + 2) * 10.0
            try:
                actor_vehicle = self.world.spawn_actor(bp_vehicle, point)
                actor_vehicle.set_simulate_physics(False)

                # move to origin point
                actor_vehicle.set_transform(carla.Transform())

                self.agents[agent_id] = TrafficAgent(actor_vehicle, agent_id, self.world)
                self.agents[agent_id].update_input(frame_id, trans, interp_num)
            except:
                print('cannot spawn actor')
        else:
            # update
            self.agents[agent_id].update_input(frame_id, trans, interp_num)

    def update_outmoded_agents(self, frame_id):
        for agent_id in list(self.agents):
            agent = self.agents[agent_id]
            frame_delta = abs(frame_id - agent.frame_id)
            if frame_delta < 3:
                continue
            elif frame_delta < 10:
                # move to origin point
                # to avoid rendering
                agent.carla_actor.set_transform(carla.Transform())
            elif frame_delta < 30:
                # del agent
                agent.carla_actor.destroy()
                self.agents.pop(agent_id)
            else:
                agent.carla_actor.destroy()
                self.agents.pop(agent_id)
        print("num of alive actors: "+str(len(self.agents)))

    def update_display(self):
        for agent in self.agents.values():
            agent.update_display()


class CarlaBridgeNode(Node):
    def __init__(self):
        super().__init__('carla_bridge')

        self.declare_parameters(
            namespace='',
            parameters=[
                ('carla_settings.port', 2000),
                ('carla_settings.host', 'localhost'),
                ('carla_settings.synchronous_mode', False),
                ('carla_settings.timeout', 30.0),
                ('carla_settings.hud.width', 1440),
                ('carla_settings.hud.height', 900),
                ('carla_settings.gamma', 2.2),
                ('carla_settings.rolename', 'inceptio'),
                ('carla_settings.filter', 'vehicle.tesla.cybertruck'),
                ('carla_settings.manual_control', True),
            ])

        self.args = argparse.Namespace()
        self.args.port = self.get_parameter('carla_settings.port').value
        self.args.host = self.get_parameter('carla_settings.host').value
        self.args.synchronous_mode = self.get_parameter('carla_settings.synchronous_mode').value
        self.args.timeout = self.get_parameter('carla_settings.timeout').value
        self.args.hud_width = self.get_parameter('carla_settings.hud.width').value
        self.args.hud_height = self.get_parameter('carla_settings.hud.height').value
        self.args.gamma = self.get_parameter('carla_settings.gamma').value
        self.args.rolename = self.get_parameter('carla_settings.rolename').value
        self.args.filter = self.get_parameter('carla_settings.filter').value
        self.args.manual_control = self.get_parameter('carla_settings.manual_control').value

        # self.args.map = 'Town06'
        self.args.map = 'jinan'
        # self.args.map = None
        # cwd = os.getcwd()
        # print(cwd)
        # self.args.xodr_path = 'hdmap/ad_map/ad_map_server/resource/jinan_overlap.xodr'
        #self.args.xodr_path = 'resource/jinan_overlap.xodr'
        self.args.xodr_path = 'resource/jinan_two_lanes.xodr'
        #self.coord_trans = CoordTrans()

        self.carla_client = self.setup_carla()
        self.carla_hud = HUD(self.args.hud_width, self.args.hud_height)
        
        if self.args.map is not None:
            print('load map %r.' % self.args.map)
            world = self.carla_client.load_world(self.args.map)
        elif self.args.xodr_path is not None and os.path.exists(self.args.xodr_path):
            with open(self.args.xodr_path) as od_file:
                try:
                    data = od_file.read()
                except OSError:
                    print('file could not be readed.')
                    sys.exit()
            print('load opendrive map %r.' % os.path.basename(self.args.xodr_path))
            vertex_distance = 2.0  # in meters
            max_road_length = 50000.0 # in meters
            wall_height = 1.0      # in meters
            extra_width = 0.6      # in meters
            world = self.carla_client.generate_opendrive_world(
                data, carla.OpendriveGenerationParameters(
                    vertex_distance=vertex_distance,
                    max_road_length=max_road_length,
                    wall_height=wall_height,
                    additional_width=extra_width,
                    smooth_junctions=True,
                    enable_mesh_visibility=True))
        else:
            world = self.carla_client.get_world()

        self.carla_world = World(world, self.carla_hud, self.args)

        if self.args.manual_control:
            self.key_ops = {
                pygame.K_LEFT : self.key_callback_lane_change,
                pygame.K_RIGHT : self.key_callback_lane_change,
                pygame.K_UP : self.key_callback_lane_change,
            }
            
            self.controller = KeyboardControl(self.carla_world, self.key_ops)    
        else:
            self.controller = None

        self.last_msg_header = None

        # self.fps_display_ = 1.0
        # self.fps_traffic_input = 1.0
        self.data_clock = pygame.time.Clock()

        self.traffic_agent_mgr = TrafficAgentManager(world)

        #self.ego_truck = self.setup_ego_truck()
        # self.model3_bp = self.carla_world.world.get_blueprint_library().find('vehicle.tesla.model3')
        # self.model3_bp.set_attribute('color', '255,255,255')
        # self.traffic_init = False
        # self.traffic_vehicle_number = 0
        self._waypoint_buffer = None
        self._buffer_size = 10000
        self.frame_id = 0
        self.fuel_total = 0.0

        self.display_update_period = 0.02 # 50 hz
        self.display_update_timer = self.create_timer(self.display_update_period, 
            self.display_update_callback)

        self.sub_traffic = self.create_subscription(
            PredictionResult,
            'PredictionResult',
            self.traffic_callback,
            10)
        
        self.sub_trucksim_debug = self.create_subscription(
            VehicleModelOutput,
            'VehicleModelOutput_Debug',
            self.trucksim_output_callback,
            10)

        self.sub_planning = self.create_subscription(
            PlanningResult,
            "planning_result",
            self.planner_result_callback,
            10)

        self.pub_lane_change = self.create_publisher(LaneChangeMsgs, 'LaneChangeMsgs', 10)

        self.models = []

    def key_callback_lane_change(self, key):
        lane_change_op = 0.0
        if key == pygame.K_LEFT:
            lane_change_op = -1.0
        elif key == pygame.K_RIGHT:
            lane_change_op = 1.0
        
        #print('lane change to {}'.format(lane_change_op))

        if self.last_msg_header != None:
            lane_change_msg = LaneChangeMsgs()
            lane_change_msg.header = self.last_msg_header
        
            lane_change_msg.lanechangeop = float(lane_change_op)
            self.pub_lane_change.publish(lane_change_msg)

    def display_update_callback(self):
        if self.controller != None:
            if self.controller.parse_events():
                return

        self.traffic_agent_mgr.update_display()
        self.carla_world.tick(self.data_clock)
        self.carla_world.render(self.carla_hud.display)
        

    def planner_result_callback(self,msg):
        self.last_msg_header = msg.header

        self.planner_result = msg.waypoints
        #self._waypoint_buffer = deque(maxlen=self._buffer_size)
        self._waypoint_buffer = []
        for point in self.planner_result:
            self._waypoint_buffer.append(point)
        self.draw_waypoints(self._waypoint_buffer)

    def traffic_callback(self, msg):
        self.last_msg_header = msg.header

        fps_display = self.carla_hud._server_clock.get_fps()
        fps_data = self.data_clock.get_fps()
        try:
            interp = fps_display / fps_data
        except:
            interp = 1.0
        
        if interp < 1.0 :
            interp = 1.0

        frame_id = int(msg.header.frame_id)
        self.frame_id = frame_id
        self.carla_hud.frame_id = frame_id
        # print('recv frame_id {}, num {}, at fps : {}'.format(frame_id, len(msg.frame), interp))
        if len(msg.frame) <= 0:
            return

        # TODO : let's use another UI thread 
        #t = Thread()

        # we only display current frame
        perception_data = msg.frame[0]
        print('recv obstacles : {}'.format(len(perception_data.obstacles)))

        for i in range(len(perception_data.obstacles)):
            obstacle = perception_data.obstacles[i]
            vehicle_id = obstacle.id

            trans = carla.Transform()
            trans.location.x = obstacle.center.x
            # TODO : y 
            #trans.location.y = obstacle.center.y
            trans.location.y = 0.0 - obstacle.center.y
            trans.location.z = obstacle.center.z

            # TODO : replace speed to rotation
            yaw = obstacle.yaw - 90
            trans.rotation.pitch = 0.0
            trans.rotation.yaw = yaw
            trans.rotation.roll = 0.0
            self.traffic_agent_mgr.update_input(vehicle_id, frame_id, trans, interp)

        # remove old agent
        self.traffic_agent_mgr.update_outmoded_agents(frame_id)
        self.data_clock.tick()

    def draw_waypoints(self, waypoints):
        # sampel waypoints 
        waypoints = waypoints

        def waypoint2location(waypoint):
            pts = [waypoint.center.x, -waypoint.center.y, waypoint.center.z]
            loc = carla.Location(x=pts[0], y=pts[1], z=pts[2])
            return loc

        for i in range(0, len(waypoints)-2):
            pts = waypoint2location(waypoints[i])
            pts_next = waypoint2location(waypoints[i+1])

            self.carla_world.world.debug.draw_line(pts, pts_next, life_time=0.5)
            self.carla_world.world.debug.draw_point(pts, color=carla.Color(0,0,255), life_time=0.5)
            

        pts = waypoint2location(waypoints[-2])
        pts_end = waypoint2location(waypoints[-1])
        self.carla_world.world.debug.draw_arrow(pts, pts_end, life_time=0.5)
        
        # for i in range(0, len(waypoints)-1, 5):
        #     begin = self.coord_trans.trucksim_to_carla(waypoints[i].center.x, waypoints[i].center.y) + [waypoints[i].center.z]
        #     end = self.coord_trans.trucksim_to_carla(waypoints[i+1].center.x, waypoints[i+1].center.y) + [waypoints[i+1].center.z]
        #     # if i == 0:
        #     #     print(begin)
        #     #     print(end)
        #     begin_location = carla.Location(x=begin[0], y=begin[1], z=begin[2])
        #     end_location = carla.Location(x=end[0], y=end[1], z=end[2])
        #     #self.carla_world.world.debug.draw_arrow(begin_location, end_location, arrow_size=0.3, life_time=0.5)

    def trucksim_output_callback(self, msg):
        #print(msg)
        # print(msg.xo, msg.yo, msg.zo)
        # [cx, cy] = self.coord_trans.trucksim_to_carla(msg.xo, msg.yo)
        # print("yaw="+str(msg.yaw))
        transform = carla.Transform()
        transform.location.x = msg.xo
        transform.location.y = -msg.yo
        transform.location.z = msg.zo
        transform.rotation.roll = msg.roll
        transform.rotation.pitch = msg.pitch
        transform.rotation.yaw = 0.0 - msg.yaw


        velocity = carla.Vector3D(msg.vx, msg.vy, 0)
        self.carla_hud._ego_velocity = velocity

        c = carla.VehicleControl()
        c.steer = msg.input.steer / 6.0
        c.throttle = msg.input.throttle / 100.0
        c.brake = 0.0 - msg.input.brake / 6.0
        c.gear = int(msg.gear_pos)
        self.carla_hud._ego_control = c

        # print(msg)
        # print(transform)
        self.carla_world.player.set_transform(transform)
        #self.carla_world.render(self.carla_hud.display)

        self.fuel_total = msg.total_fuel
        self.carla_hud.fuel_total = msg.total_fuel

    def setup_carla(self):
        try:
            client = carla.Client(
                host=self.args.host,
                port=self.args.port)

            self.get_logger().info("Carla Connect to {host}:{port}".format(
                host=self.args.host, port=self.args.port))

            client.set_timeout(self.args.timeout)
            return client

        except (IOError, RuntimeError) as e:
            self.get_logger().error(e)
        finally:
            del client

def main(args=None):
    #print("running carla_bridge node")
    rclpy.init(args=args)
    carla_bridge_node = CarlaBridgeNode()
    rclpy.spin(carla_bridge_node)
    carla_bridge_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()