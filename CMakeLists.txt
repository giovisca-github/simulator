cmake_minimum_required(VERSION 3.8)
project(my_cpp_pkg)
# set(CMAKE_CXX_STANDARD 20)

# if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#   add_compile_options(-Wall -Wextra -Wpedantic)
# endif()

find_package(Eigen3 REQUIRED)


include_directories(include)
include_directories(${EIGEN_INCLUDE_DIR})
# file(GLOB_RECURSE SOURCES
# src/bridge/*.cpp
# src/common/*.cpp)

set(SOURCES
    src/bridge/bridge.cpp
    src/bridge/server.cpp
    src/common/car.cpp
    src/common/car_state.cpp
    src/common/math_stuff.cpp
)


add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE
  zmq
  zmqpp)

add_subdirectory(Test)

# # find dependencies
# find_package(ament_cmake REQUIRED)
# # uncomment the following section in order to fill in
# # further dependencies manually.
# # find_package(<dependency> REQUIRED)

# find_package(rclcpp REQUIRED)
# add_executable(test_node src/my_node.cpp)
# ament_target_dependencies(test_node rclcpp)
# install(TARGETS
#   test_node
#   DESTINATION lib/${PROJECT_NAME}
# )

# # ament_package()
