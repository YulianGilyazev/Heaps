
cmake_minimum_required(VERSION 2.8)

project(project)

#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SOURCE_EXE main.cpp)

include_directories(./Fibonacci_heap)
include_directories(./Binary_heap)
include_directories(./Binomial_heap)


add_executable(main ${SOURCE_EXE})

add_subdirectory(Fibonacci_heap)
add_subdirectory(Binomial_heap)
add_subderictory(Binary_heap)


target_link_libraries(main Fibonacci_heap)
target_link_libraries(main Binary_heap)
target_link_libraries(main Binomial_heap)

#---------------------GTEST-------------------------------

option(BUILD_TESTS "Build unit tests" OFF)

if (BUILD_TESTS)
	add_subdirectory(ext/gtest-1.8.0)
	include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

	set(SOURCE_EXE tests.cpp)

	add_executable(tests ${SOURCE_EXE})

	target_link_libraries(tests Binomial_heap)
	target_link_libraries(tests Binary_heap)
	target_link_libraries(tests Fibonacci_heap)
	target_link_libraries(tests gtest gtest_main)
endif()