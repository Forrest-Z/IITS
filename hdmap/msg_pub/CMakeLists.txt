cmake_minimum_required(VERSION 3.5)
project(msg_pub)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)

find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(ad_map_server REQUIRED)
find_package(fead_interfaces REQUIRED)

if(NOT TARGET GTest::gtest)
  find_package(GTest QUIET CONFIG)
  if(NOT GTest_FOUND)
    # As Ubuntu never ships precompiled gtest libraries, build them on-the-fly
    # from source requires gtest-dev package to be intalled
    set(gtest_source_paths /usr/src/googletest/ /usr/src/gtest/
                           ${GTEST_SRC_PATH})
    foreach(src_path IN LISTS gtest_source_paths)
      if(EXISTS ${src_path}/CMakeLists.txt)
        set(gtest_src_path ${src_path})
        break()
      endif()
    endforeach()
    if(gtest_src_path)
      message(STATUS "Using gtest source build from: ${gtest_src_path}")
      set(BUILD_SHARED_LIBS_SAVED "${BUILD_SHARED_LIBS}")
      set(BUILD_SHARED_LIBS OFF)
      set(CMAKE_POSITION_INDEPENDENT_CODE ON)
      add_subdirectory(${gtest_src_path} gtest EXCLUDE_FROM_ALL)
      set(BUILD_SHARED_LIBS "${BUILD_SHARED_LIBS_SAVED}")
      add_library(GTest::gtest ALIAS gtest)
      add_library(GTest::gtest_main ALIAS gtest_main)
    else()
      message(ERROR "Neither installed gtest nor sources found.")
    endif()
  else()
    message(STATUS "Using installed gtest")
  endif()
endif()

add_executable(run_routing_node src/test_routing.cpp)
ament_target_dependencies(run_routing_node rclcpp std_msgs ad_map_server
                          fead_interfaces)

add_executable(run_accessLaneID_node src/test_access_lane_id.cpp)
ament_target_dependencies(run_accessLaneID_node rclcpp std_msgs ad_map_server
                          fead_interfaces)

add_executable(run_accessLeftLane_node src/test_access_left_lane.cpp)
ament_target_dependencies(run_accessLeftLane_node rclcpp std_msgs ad_map_server
                          fead_interfaces)

add_executable(run_accessRightLane_node src/test_access_right_lane.cpp)
ament_target_dependencies(run_accessRightLane_node rclcpp std_msgs
                          ad_map_server fead_interfaces)

add_executable(run_getSlop_node src/test_get_slop.cpp)
ament_target_dependencies(run_getSlop_node rclcpp std_msgs ad_map_server
                          fead_interfaces)

add_executable(run_getZ_node src/test_get_z.cpp)
ament_target_dependencies(run_getZ_node rclcpp std_msgs ad_map_server
                          fead_interfaces)

add_executable(run_get_lane_segment_from_id
               src/test_get_lane_segement_from_id.cpp)
ament_target_dependencies(run_get_lane_segment_from_id rclcpp std_msgs
                          ad_map_server fead_interfaces)
target_link_libraries(run_get_lane_segment_from_id GTest::gtest)

add_executable(run_get_nearest_lane_segments_from_p2d
               src/test_get_nearest_lane_segments_from_p2d.cpp)
ament_target_dependencies(run_get_nearest_lane_segments_from_p2d rclcpp
                          std_msgs ad_map_server fead_interfaces)

add_executable(run_get_nearest_lane_segments_from_p3d
               src/test_get_nearest_lane_segments_from_p3d.cpp)
ament_target_dependencies(run_get_nearest_lane_segments_from_p3d rclcpp
                          std_msgs ad_map_server fead_interfaces)

add_executable(run_get_nearest_center_polyline_p2d
               src/test_get_nearest_center_polyline_p2d.cpp)
ament_target_dependencies(run_get_nearest_center_polyline_p2d rclcpp std_msgs
                          ad_map_server fead_interfaces)

add_executable(run_get_nearest_center_polyline_p3d
               src/test_get_nearest_center_polyline_p3d.cpp)
ament_target_dependencies(run_get_nearest_center_polyline_p3d rclcpp std_msgs
                          ad_map_server fead_interfaces)

add_executable(run_get_frenet_projection_center_polyline_2d
               src/test_get_frenet_projection_center_polyline_2d.cpp)
ament_target_dependencies(run_get_frenet_projection_center_polyline_2d rclcpp
                          std_msgs ad_map_server fead_interfaces)

add_executable(run_get_frenet_projection_center_polyline_3d
               src/test_get_frenet_projection_center_polyline_3d.cpp)
ament_target_dependencies(run_get_frenet_projection_center_polyline_3d rclcpp
                          std_msgs ad_map_server fead_interfaces)

install(
  TARGETS run_routing_node
          run_accessLaneID_node
          run_accessLeftLane_node
          run_accessRightLane_node
          run_getSlop_node
          run_getZ_node
          run_get_lane_segment_from_id
          run_get_nearest_lane_segments_from_p2d
          run_get_nearest_lane_segments_from_p3d
          run_get_nearest_center_polyline_p2d
          run_get_nearest_center_polyline_p3d
          run_get_frenet_projection_center_polyline_2d
          run_get_frenet_projection_center_polyline_3d
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights uncomment
  # the line when a copyright and license is not present in all source files
  # set(ament_cmake_copyright_FOUND TRUE) the following line skips cpplint (only
  # works in a git repo) uncomment the line when this package is not in a git
  # repo set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
