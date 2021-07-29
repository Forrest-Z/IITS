cmake_minimum_required(VERSION 3.5)
project(ad_map_server)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

include(../cmake/compile-options.cmake)
include(../cmake/hardening.cmake)
include(../cmake/testing.cmake)
include(../cmake/warnings.cmake)
include(../cmake/apidoc.cmake)
include(../cmake/python-binding.cmake)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(fead_interfaces REQUIRED)

find_package(allspark REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

set(LIBRARIES "")
set(INCLUDE_DIRS "")
set(ALL_SPARK_INCLUDE_DIR
    ${CMAKE_CURRENT_LIST_DIR}/../../../third_party/allspark)
set(ALL_SPARK_LIB_DIR ${CMAKE_CURRENT_LIST_DIR}/../../../../build/allspark)

# message(${PROJECT_NAME}  ------    ${LIBRARIES})

# ad_map_access
find_package(ad_map_access REQUIRED)
get_target_property(ACCESS_INCLUDE ad_map_access INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(ACCESS_LIBRARIES ad_map_access INTERFACE_LINK_LIBRARIES)
list(APPEND INCLUDE_DIRS ${ACCESS_INCLUDE})
list(APPEND LIBRARIES ${ACCESS_LIBRARIES})

# message(${PROJECT_NAME}  ------    ${LIBRARIES})

# ad_map_opendrive_reader
find_package(ad_map_opendrive_reader REQUIRED)
get_target_property(AD_MAP_OPENDRIVE_READER_INCLUDE ad_map_opendrive_reader
                    INTERFACE_INCLUDE_DIRECTORIES)
list(APPEND INCLUDE_DIRS ${AD_MAP_OPENDRIVE_READER_INCLUDE})
list(APPEND LIBRARIES ad_map_opendrive_reader)

# ad_physics
find_package(ad_physics REQUIRED)
get_target_property(AD_PHYSICS_INCLUDE ad_physics INTERFACE_INCLUDE_DIRECTORIES)
list(APPEND INCLUDE_DIRS ${AD_PHYSICS_INCLUDE})
list(APPEND LIBRARIES ad_physics)

# spdlog
find_package(spdlog REQUIRED)
get_target_property(SPDLOG_INCLUDE spdlog::spdlog INTERFACE_INCLUDE_DIRECTORIES)
list(APPEND INCLUDE_DIRS ${SPDLOG_INCLUDE})
list(APPEND LIBRARIES spdlog::spdlog)

find_package(Boost REQUIRED COMPONENTS program_options filesystem system)
get_target_property(BOOST_PROGRAM_OPTIONS_INTERFACE_INCLUDE_DIRS
                    Boost::program_options INTERFACE_INCLUDE_DIRECTORIES)
list(APPEND INCLUDE_DIRS ${BOOST_PROGRAM_OPTIONS_INTERFACE_INCLUDE_DIRS})
list(APPEND LIBRARIES Boost::program_options)
get_target_property(BOOST_FILESYSTEM_INTERFACE_INCLUDE_DIRS Boost::filesystem
                    INTERFACE_INCLUDE_DIRECTORIES)
list(APPEND INCLUDE_DIRS ${BOOST_FILESYSTEM_INTERFACE_INCLUDE_DIRS})
list(APPEND LIBRARIES Boost::filesystem)

# message(${PROJECT_NAME}  ------    ${LIBRARIES})
link_directories(${ALL_SPARK_LIB_DIR})

# LINK_LIBRARIES(boost_system)

# ##############################################################################
file(GLOB SRC_LIST_CPP ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_LIST_CPP})
list(REMOVE_ITEM SRC_LIST_CPP ${PROJECT_SOURCE_DIR}/src/map_server.cpp)
list(REMOVE_ITEM SRC_LIST_CPP ${PROJECT_SOURCE_DIR}/src/ad_to_ros_map.cpp)
add_library(ad_map_server_lib ${SRC_LIST_CPP})

target_include_directories(
  ${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include
                         ${PROJECT_SOURCE_DIR}/src ${ALL_SPARK_INCLUDE_DIR})

target_include_directories(
  ad_map_server_lib PUBLIC ${INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include
                           ${PROJECT_SOURCE_DIR}/src ${ALL_SPARK_INCLUDE_DIR})

ament_target_dependencies(${PROJECT_NAME} rclcpp std_msgs geometry_msgs
                          fead_interfaces)
target_link_libraries(${PROJECT_NAME} ad_map_access ad_map_opendrive_reader
                      ad_physics boost_system allspark)
ament_target_dependencies(ad_map_server_lib rclcpp std_msgs geometry_msgs
                          fead_interfaces)
target_link_libraries(ad_map_server_lib ad_map_access ad_map_opendrive_reader
                      ad_physics boost_system allspark)

install(TARGETS ad_map_server DESTINATION lib/${PROJECT_NAME})
install(TARGETS ad_map_server_lib DESTINATION lib/${PROJECT_NAME})

# file(GLOB_RECURSE RES_FILES ${PROJECT_SOURCE_DIR}/resource/*) install(FILES
# ${RES_FILES} DESTINATION share/${PROJECT_NAME}/resource)

# file(GLOB_RECURSE RES_FILES ${PROJECT_SOURCE_DIR}/resource/*)

# message(********* ${RES_FILES}) install(FILES ${RES_FILES} DESTINATION
# share/${PROJECT_NAME}/resource)

install(DIRECTORY resource DESTINATION share/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
