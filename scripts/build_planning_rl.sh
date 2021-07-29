#!/bin/sh

colcon build --packages-select \
spdlog \
ad_physics \
ad_map_access \
ad_map_opendrive_reader \
ad_map_server \
ad_map_server_py \
carla_bridge \
fead_interfaces \
fead_monitor \
scenario_runner \
trajectory_planner \
trucksim_bridge \
traffic_sim \
perfect_control \
pid_controller \
carla_bridge \
carla_msgs \
rl_longitudinal \
rl_decision_making \
trucksim_bridge_trailer \
png_controller \
planning_png



