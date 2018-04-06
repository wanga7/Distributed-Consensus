cmake_minimum_required(VERSION 2.8)
project (sockets)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -g")
include_directories("${CMAKE_SOURCE_DIR}")

add_library(practicalsocket PracticalSocket.cpp)
target_link_libraries (practicalsocket pthread rt)

add_executable(UDPEchoClient UDPEchoClient.cpp)
add_executable(UDPEchoServer UDPEchoServer.cpp)
target_link_libraries(UDPEchoServer practicalsocket)
target_link_libraries(UDPEchoClient practicalsocket)

