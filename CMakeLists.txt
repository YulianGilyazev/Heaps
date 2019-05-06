cmake_minimum_required(VERSION 2.8)

project(project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SOURCE_EXE main.cpp)

include_directories(./Fibonacci_heap)
include_directories(./Binary_heap)
include_directories(./Binomial_heap)


add_executable(main ${SOURCE_EXE})

add_subdirectory(Fibonacci_heap)
add_subdirectory(Binomial_heap)
add_subdirectory(Binary_heap)


target_link_libraries(main Fibonacci_heap)
target_link_libraries(main Binary_heap)
target_link_libraries(main Binomial_heap)

option(BUILD_TESTS "Build unit tests" OFF)

if (BUILD_TESTS)
        #ADD_SUBDIRECTORY (gtest-1.6.0)
	enable_testing()
	
	set( CMAKE_CXX_STANDARD 14 )
	set( CMAKE_CXX_STANDARD_REQUIRED on )
	add_executable(tests test.cpp)

	#target_link_libraries(tests ${GTEST_LIBRARY_DEBUG} ${GTEST_MAIN_LIBRARY_DEBUG})
        #target_link_libraries(tests ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY})

	target_link_libraries(tests Binomial_heap)
	target_link_libraries(tests Binary_heap)
	target_link_libraries(tests Fibonacci_heap)
	#target_link_libraries(tests gtest gtest_main)
	add_test( tests tests )
endif()
