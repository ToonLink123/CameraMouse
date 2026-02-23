 cmake_minimum_required(VERSION 3.16)
project(HandControl)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

include_directories(include)

add_executable(handcontrol src/main.cpp)

target_link_libraries(handcontrol ${OpenCV_LIBS})