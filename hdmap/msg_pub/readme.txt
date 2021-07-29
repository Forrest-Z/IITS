test ad_map_server

1. go to the ros2 workspace
$ cd ~/code/fead_ws

2. source the ros2 environment
~/code/fead_ws$ source /opt/ros/eloquent/setup.bash

3. build the msg_pub package  (optional)
~/code/fead_ws$ colcon build --packages-select msg_pub

4. add the environment
~/code/fead_ws$ source ./install/setup.bash

5. start the ad_map_server with Town06
~/code/fead_ws$ ros2 run ad_map_server ad_map_server ./src/hdmap/ad_map/ad_map_server/src/HDMAP/Town06_config.txt
start the ad_map_server with jinan
~/code/fead_ws$ ros2 run ad_map_server ad_map_server ./src/hdmap/ad_map/ad_map_server/resource/jinan_two_lanes_config.txt

6. run the AccessLaneID service test node
input the position in which mathes unique lane:
~/code/fead_ws$ ros2 run msg_pub run_accessLaneID_node 75.6638 -41.8271 -0.000776613
input the position in which mathes multiple lane, but the service only return one matched lane ID:
~/code/fead_ws$ ros2 run msg_pub run_accessLaneID_node 660.204 -38.1838 -0.0284984

7. run the AccessLeftLane service test node
~/code/fead_ws$ ros2 run msg_pub run_accessLeftLane_node 75.6638 -41.8271 -0.000776613

8. run the AccessRightLane service test node
~/code/fead_ws$ ros2 run msg_pub run_accessRightLane_node 75.6638 -41.8271 -0.000776613

The following example will meet an error. Because the map server only consider points around the road surface.
~/code/fead_ws$ ros2 run msg_pub run_accessRightLane_node 75.6638 -41.8271 1


8. run the Routing service test node
~/code/fead_ws$ ros2 run msg_pub run_routing_node 75.6638 -41.8271 -0.000776613 601.204 -38.1838 -0.0284984

9. run the AccessLaneID service test node for edge case
~/code/fead_ws$ ros2 run msg_pub run_accessLaneID_node 0 -46.874489837646486 0.0
return:
[INFO] [rclcpp]: Lane ID: 0
which means that the AccessLaneID service cannot find a reasonable laneID for the input postion.

10. run the GetSlop service test node for edge case
~/code/fead_ws$ ros2 run msg_pub run_getSlop_node -308.181 -353.725 427.773

11. run the GetZ service test node for edge case
~/code/fead_ws$ ros2 run msg_pub run_getZ_node -308.181 -353.725

