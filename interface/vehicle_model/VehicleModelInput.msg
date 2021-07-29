#
# Copyright (c) 2020 Inceptio Corporation.
#
# This work is licensed under the terms of the MIT license.
# For a copy, see <https://opensource.org/licenses/MIT>.
#

std_msgs/Header header

#both
float32 throttle #float32 pedalpos_pct                  
float32 brake    #float32 xbr1_externalaccele         
float32 steer    #float32 steerwhangle_rad             
float32 ctrlmode  # when brake

float32 gear

#simulink
float32 grade_deg        #slope(built-in trucksim)

# for control & vehicle model
int64 control_frame_id

              