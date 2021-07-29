#!/usr/bin/python3
#
# Copyright (c) 2020 Inceptio
#

from collections import deque
from fead_interfaces.srv._access_lane_id import *
from fead_interfaces.srv._access_left_lane import *
from fead_interfaces.srv._access_right_lane import *
from fead_interfaces.srv._routing import *
from fead_interfaces.srv._get_z import *
import rclpy
from rclpy.node import Node
import math
import numpy as np

from trajectory_planner.coord_tranform import Coord_Trans
class HDmap(Node):
    def __init__(self):
        super().__init__('HDmap_fake')
        self.node = self
        self.req_lane_id = self._create_client(AccessLaneID, 'AccessLaneID')
        self.req_left_lane = self._create_client(AccessLeftLane, 'AccessLeftLane')
        self.req_right_lane = self._create_client(AccessRightLane, 'AccessRightLane')
        self.req_routing = self._create_client(Routing, 'Routing')
        self.req_Z = self._create_client(GetZ, 'GetZ')
        self.coord_trans = Coord_Trans(-225.151904, -6337.384475)

    def _create_client(self, service_tocall, service_name):
        service = self.node.create_client(service_tocall, service_name)
        while not service.wait_for_service(timeout_sec=0.1):
            self.node.get_logger().info('service '+service_name+ ' not available, waiting again...')
        self.node.get_logger().info('connected to service '+service_name)
        return service

    def _calc_relative_x_h(self, waypoint_buffer):
        def calc_distance(x1,y1,x2,y2):
            return math.sqrt((x1-x2)**2+(y1-y2)**2)
        x = [0]
        grad = [waypoint_buffer[0][2]]
        for i in range(len(waypoint_buffer)-1):
            x.append(x[i]+calc_distance(waypoint_buffer[i][0], waypoint_buffer[i][1], waypoint_buffer[i+1][0], waypoint_buffer[i+1][1]))
            grad.append(waypoint_buffer[i+1][2])
        return x, grad

    def GlobalPlanner(self, start_pos, end_pos):
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
        rclpy.spin_until_future_complete(self.node, result, timeout_sec = 0.1)
        if result.result() is not None:
            return result.result()
        else:
            self.node.get_logger().error('Exception while calling service get Z: %r' % result.exception())
            print(str(req.x)+" "+str(req.y))
            return None


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
        # print(x)
        return x, grad 


def main(args=None):
    rclpy.init(args=args)
    node  = Node('HDmap')
    map = HDmap()
    atan = []
    deltaz = []
    deltaxy = []
    getz = map.query_z(-282.034, -6311.39)
    print (getz)

if __name__ == '__main__':
    main()