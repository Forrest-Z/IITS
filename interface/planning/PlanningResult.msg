#
# Copyright (c) 2020 Inceptio Corporation.
#
# This work is licensed under the terms of the MIT license.
# For a copy, see <https://opensource.org/licenses/MIT>.
#


uint8 EMERGENCY_ACCELERATION = 0
uint8 EMERGENCY_VELOCITY = 1
uint8 EMERGENCY_POSITION = 3

std_msgs/Header header

Waypoint[] waypoints
float32 planner_status
bool emergency_stop