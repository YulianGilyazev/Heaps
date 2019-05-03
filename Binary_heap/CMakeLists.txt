cmake_minimum_required(VERSION 2.8)

project(Binary_heap)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

set(SOURCE_LIB binary_heap.cpp)
add_library(Binary_heap STATIC ${SOURCE_LIB})

