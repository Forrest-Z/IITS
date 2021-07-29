#!/usr/bin/python3
#
# Copyright (c) 2020 Inceptio
#
""" This module contains PID controllers to perform lateral and longitudinal control. """

from collections import deque
import math

import numpy as np


class VehiclePIDController():
    def __init__(self, args_lateral=None, args_longitudinal=None):
        """
        :param args_lateral: dictionary of arguments to set the lateral PID controller using the following semantics:
                             K_P -- Proportional term
                             K_D -- Differential term
                             K_I -- Integral term
        :param args_longitudinal: dictionary of arguments to set the longitudinal PID controller using the following
        semantics:
                             K_P -- Proportional term
                             K_D -- Differential term
                             K_I -- Integral term
        """
        if not args_lateral:
            args_lateral = {'K_P': 1.0, 'K_D': 0.0, 'K_I': 0.0}
        if not args_longitudinal:
            args_longitudinal = {'K_P': 1.0, 'K_D': 0.0, 'K_I': 0.0}

        self._lon_controller = PIDLongitudinalController( **args_longitudinal)
        self._lat_controller = PIDLateralController( **args_lateral)

    def run_step(self, target_speed, waypoint, velocity, vehicle_location, vehicle_rotation ):
        """
        Execute one step of control invoking both lateral and longitudinal PID controllers to reach a target waypoint
        at a given target_speed.

        :param target_speed: desired vehicle speed
        :param waypoint: target location encoded as a waypoint
        :return: distance (in meters) to the waypoint
        """
        throttle = self._lon_controller.run_step(target_speed, velocity)
        steering = self._lat_controller.run_step(waypoint, vehicle_location, vehicle_rotation)

        brake = 0.0    


        return steering, throttle, brake


class PIDLongitudinalController():
    """
    PIDLongitudinalController implements longitudinal control using a PID.
    """

    def __init__(self, K_P=1.0, K_D=0.0, K_I=0.0, dt=0.03):
        """
        :param vehicle: actor to apply to local planner logic onto
        :param K_P: Proportional term
        :param K_D: Differential term
        :param K_I: Integral term
        :param dt: time differential in seconds
        """
        self._K_P = K_P
        self._K_D = K_D
        self._K_I = K_I
        self._dt = dt
        self._e_buffer = deque(maxlen=30)
        self.long_throttle_count = 0

    def long_throttle_check(self, throttle):
        if throttle < 0.9:
            self.long_throttle_count = 0
            return False
        else:
            if self.long_throttle_count>10:
                self.long_throttle_count = 0
                return True
            else:
                self.long_throttle_count += 1
                return False

    def run_step(self, target_speed, velocity, debug=False):
        """
        Execute one step of longitudinal control to reach a given target speed.

        :param target_speed: target speed in Km/h
        :return: throttle control in the range [0, 1]
        """
        current_speed = velocity

        if debug:
            print('Current speed = {}'.format(current_speed))
        
        throttle_control = self._pid_control(target_speed, current_speed)
        return throttle_control

    def _pid_control(self, target_speed, current_speed):
        """
        Estimate the throttle of the vehicle based on the PID equations

        :param target_speed:  target speed in Km/h
        :param current_speed: current speed of the vehicle in Km/h
        :return: throttle control in the range [0, 1]
        """
        _e = (target_speed - current_speed)
        self._e_buffer.append(_e)

        if len(self._e_buffer) >= 2:
            _de = (self._e_buffer[-1] - self._e_buffer[-2]) / self._dt
            _ie = sum(self._e_buffer) * self._dt
        else:
            _de = 0.0
            _ie = 0.0

        return np.clip((self._K_P * _e) + (self._K_D * _de / self._dt) + (self._K_I * _ie * self._dt), 0.0, 1.0)


class PIDLateralController():
    """
    PIDLateralController implements lateral control using a PID.
    """

    def __init__(self, K_P=1.0, K_D=0.0, K_I=0.0, dt=0.01):
        """
        :param vehicle: actor to apply to local planner logic onto
        :param K_P: Proportional term
        :param K_D: Differential term
        :param K_I: Integral term
        :param dt: time differential in seconds
        """
        self._K_P = K_P
        self._K_D = K_D
        self._K_I = K_I
        self._dt = dt
        self._e_buffer = deque(maxlen=10)

    def run_step(self, waypoint, vehicle_location, vehicle_rotation):
        """
        Execute one step of lateral control to steer the vehicle towards a certain waypoin.

        :param waypoint: target waypoint
        :return: steering control in the range [-1, 1] where:
            -1 represent maximum steering to left
            +1 maximum steering to right
        """
        # print(waypoint, vehicle_location, vehicle_rotation)
        return self._pid_control(waypoint, vehicle_location, vehicle_rotation)

    def _pid_control(self, waypoint, vehicle_location, vehicle_rotation):
        """
        Estimate the steering angle of the vehicle based on the PID equations

        :param waypoint: target waypoint
        :param vehicle_transform: current transform of the vehicle
        :return: steering control in the range [-1, 1]
        """
        ## Vehicle transform should be [x,y,z, roll, pitch, yaw]

        v_begin = np.array(vehicle_location)
        v_end = v_begin + np.array([math.cos(math.radians(vehicle_rotation)),
                                         math.sin(math.radians(vehicle_rotation)),0])
        # print("vbegin"+str(v_begin)+"vend"+ str(v_end)+"waypoint"+str(waypoint))
        v_vec = np.array([v_end[0] - v_begin[0], v_end[1] - v_begin[1], 0.0])
        w_vec = np.array([waypoint[0] -
                          v_begin[0], waypoint[1] -
                          v_begin[1], 0.0])
        _dot = math.acos(np.clip(np.dot(w_vec, v_vec) /
                                 (np.linalg.norm(w_vec) * np.linalg.norm(v_vec)), -1.0, 1.0))

        _cross = np.cross(v_vec, w_vec)
        if _cross[2] < 0:
            _dot *= -1.0

        self._e_buffer.append(_dot)
        if len(self._e_buffer) >= 2:
            _de = (self._e_buffer[-1] - self._e_buffer[-2]) / self._dt
            _ie = sum(self._e_buffer) * self._dt
        else:
            _de = 0.0
            _ie = 0.0
        # print("dot"+str(_dot)+"de"+str(_de)+"ie"+str(_ie))
        return np.clip((self._K_P * _dot) + (self._K_D * _de /
                                             self._dt) + (self._K_I * _ie * self._dt), -1.0, 1.0)
