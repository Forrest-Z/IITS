#
# Copyright (c) 2020 Inceptio Corporation.
#
# This work is licensed under the terms of the MIT license.
# For a copy, see <https://opensource.org/licenses/MIT>.
#

string id
string type 

geometry_msgs/Vector3 center
geometry_msgs/Vector3 size

geometry_msgs/Quaternion orientation

float32 speed
geometry_msgs/Accel acceleration

float32 yaw
float32 pitch

### extra 
uint32 parent_id # 0 if no parent available
string rolename

