cmake_minimum_required(VERSION 3.0.2)
project(bag2txt)


find_package(catkin_simple REQUIRED roscpp sensor_msgs geometry_msgs)
catkin_simple(ALL_DEPS_REQUIRED)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES bag2txt
CATKIN_DEPENDS roscpp sensor_msgs geometry_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

include_directories(${catkin_INCLUDE_DIRS})

add_executable(main src/main.cpp)

target_link_libraries(main
  ${catkin_LIBRARIES}
)
