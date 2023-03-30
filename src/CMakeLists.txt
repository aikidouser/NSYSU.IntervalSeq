cmake_minimum_required(VERSION 3.22)

message("CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
message("CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")

set (CMAKE_CXX_FLAGS "-Wall -std=c++14")

project(IntervalSequence)

add_executable(Interval main.cpp interval/interval.cpp)
