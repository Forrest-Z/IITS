uint8 LANETURN_LANE_TURN_UNDEFINED = 0
uint8 LANETURN_LEFT_MERGE = 1
uint8 LANETURN_LEFT_SPLIT = 2
uint8 LANETURN_LEFT_TURN = 3
uint8 LANETURN_RIGHT_MERGE = 4
uint8 LANETURN_RIGHT_SPLIT = 5
uint8 LANETURN_RIGHT_TURN = 6
uint8 LANETURN_STRAIGHT = 7
uint8 LANETURN_U_TURN = 8

uint8 TYPE_UNDEFINED = 0
uint8 TYPE_CITY_DRIVING = 1
uint8 TYPE_HIGHWAY_DRIVING = 2
uint8 TYPE_EMERGENCY_LANE = 3
uint8 TYPE_BIKING = 4
uint8 TYPE_SHOULDER = 5
uint8 TYPE_PARKING = 6
uint8 TYPE_PAVEMENT = 7
uint8 TYPE_MAX_LANE_TYPE = 8



std_msgs/String id
uint8 type
uint8 lane_turn

LaneBoundary left_boundary
LaneBoundary right_boundary

std_msgs/String[] predecessor_ids
std_msgs/String[] successor_ids
std_msgs/String[] left_neighbor_ids
std_msgs/String[] right_neighbor_ids
  
std_msgs/String[] merge_neighbor_ids
std_msgs/String[] split_neighbor_ids

float64 speed_limit_min_mps  
float64 speed_limit_max_mps  

CenterPolyline center_polyline

std_msgs/String[] traffic_light_ids

