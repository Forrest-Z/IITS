1. add a new map
*put .xodr file to visualization/carla/carla_bridge/resource directory
*revise self.args.xodr_path in bridge.py of carla_bridge
*put .xodr and _config.txt file to resource directory of hdmap/ad_map/ad_map_server/resource
*run map server:
~/code/fead_ws$ ros2 run ad_map_server ad_map_server ./src/hdmap/ad_map/ad_map_server/src/resource/jinan_two_lanes_config.txt
Noticed that the directory of _config.txt file should be changed according to your situation.
