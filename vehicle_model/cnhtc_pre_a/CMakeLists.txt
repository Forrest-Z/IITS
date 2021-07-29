cmake_minimum_required(VERSION 3.5)
project(cnhtc_pre_a)

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
find_package(fead_interfaces REQUIRED)

FILE(GLOB SRC_LIST_C 
  ${PROJECT_SOURCE_DIR}/src/*.cpp
  ${PROJECT_SOURCE_DIR}/src/vs_api/*.c)

# libm & libdl
LINK_LIBRARIES(m dl) 

#指定头文件目录
INCLUDE_DIRECTORIES(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/src/vs_api )

add_executable(trucksim_bridge_node ${SRC_LIST_C} src/trucksim_bridge.cpp)
ament_target_dependencies(trucksim_bridge_node rclcpp std_msgs fead_interfaces)

install(TARGETS
  trucksim_bridge_node
  DESTINATION lib/${PROJECT_NAME}
)

# file(GLOB_RECURSE RES_FILES ${PROJECT_SOURCE_DIR}/resource/*)
# install(FILES ${RES_FILES} DESTINATION share/${PROJECT_NAME}/resource)

install(DIRECTORY resource DESTINATION share/${PROJECT_NAME})
install(DIRECTORY config DESTINATION share/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
