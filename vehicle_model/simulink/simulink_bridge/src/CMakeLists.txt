#指定CMake编译最低要求版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.10.2)
#给项目命名
PROJECT(simulink)

#收集c/c++文件并赋值给变量SRC_LIST_CPP  ${PROJECT_SOURCE_DIR}代表区当前项目录
FILE(GLOB SRC_LIST_CPP ${PROJECT_SOURCE_DIR}/*.cpp ${PROJECT_SOURCE_DIR}/ert/TCU/*.cpp ${PROJECT_SOURCE_DIR}/ert/Engine_ECU/*.cpp
${PROJECT_SOURCE_DIR}/ert/Braking/*.cpp ${PROJECT_SOURCE_DIR}/ert/SteerWhlMdl/*.cpp 
${PROJECT_SOURCE_DIR}/ert/CNHTC_VEHICLE_MODEL_PureSL/*.cpp  ${PROJECT_SOURCE_DIR}/ert/_sharedutils/*.cpp)

LINK_LIBRARIES(m) 

#指定头文件目录
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/ert/TCU ${PROJECT_SOURCE_DIR}/ert/Engine_ECU 
${PROJECT_SOURCE_DIR}/ert/Braking  ${PROJECT_SOURCE_DIR}/ert/SteerWhlMdl  
${PROJECT_SOURCE_DIR}/ert/CNHTC_VEHICLE_MODEL_PureSL ${PROJECT_SOURCE_DIR}/ert/_sharedutils)
#指定生成库文件的目录
# SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
#去变量SRC_LIST_CPP 与SRC_LIST_C 指定生成libmyprint 动态库   默认生成静态库  SHARED指定生成库类型为动态库
add_executable(simulink ${SRC_LIST_CPP})