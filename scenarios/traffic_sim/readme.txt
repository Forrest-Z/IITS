1. add traffic flow dataset
*copy dataset to resource directory
*In setup.py, add the dataset directory to data_files

2. change traffic flow data
traffic_sim/traffic_sim_node.py
change the directory around Line 25
traffic_sample_dir = os.path.join(node_share_dir, 'trafficData_mapped/twoLanes/test1_selected')

3. build the node
colcon build --packages-select traffic_sim

4. run the node 
in Terminal:
ros2 run traffic_sim run_traffic_sim