cmake_minimum_required(VERSION 2.8)
project (sockets)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -g")
include_directories("${CMAKE_SOURCE_DIR}")

add_library(practicalsocket PracticalSocket.cpp)
target_link_libraries (practicalsocket pthread rt)

add_executable(Ledger1 Ledger1.cpp)
target_link_libraries(Ledger1 practicalsocket)

add_executable(Ledger2 Ledger2.cpp)
target_link_libraries(Ledger2 practicalsocket)

add_executable(Ledger3 Ledger3.cpp)
target_link_libraries(Ledger3 practicalsocket)

add_executable(Ledger4 Ledger4.cpp)
target_link_libraries(Ledger4 practicalsocket)

add_executable(Ledger5 Ledger5.cpp)
target_link_libraries(Ledger5 practicalsocket)

