cmake_minimum_required(VERSION 2.8)

project(Binomial_heap)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

set(SOURCE_LIB binomial_heap.cpp)
add_library(Binomial_heap STATIC ${SOURCE_LIB})


