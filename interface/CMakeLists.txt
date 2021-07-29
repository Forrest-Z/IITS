cmake_minimum_required(VERSION 3.5)

project(fead_interfaces)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

FILE(GLOB_RECURSE MSG_FILES RELATIVE ${PROJECT_SOURCE_DIR} *.msg)
FILE(GLOB_RECURSE SRV_FILES RELATIVE ${PROJECT_SOURCE_DIR} *.srv)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${SRV_FILES}
  ${MSG_FILES}
  DEPENDENCIES
    builtin_interfaces
    geometry_msgs
    std_msgs
  ADD_LINTER_TESTS
)

#install(FILES mapping_rules.yaml DESTINATION share/${PROJECT_NAME})

ament_export_dependencies(rosidl_default_runtime)
ament_package()