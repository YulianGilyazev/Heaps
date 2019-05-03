cmake_minimum_required(VERSION 2.8)

project(Fibonacci_heap)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

set(SOURCE_LIB fibonacci_heap.cpp)
add_library(Fibonacci_heap STATIC ${SOURCE_LIB})



