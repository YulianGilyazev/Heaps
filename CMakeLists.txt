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
	set(GOOGLETEST_ROOT gtest/googletest CACHE STRING "Google Test source root")

	include_directories(SYSTEM
	    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}
	    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/include
	    )

	set(GOOGLETEST_SOURCES
	    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest-all.cc
	    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest_main.cc
	    )

	foreach(_source ${GOOGLETEST_SOURCES})
	    set_source_files_properties(${_source} PROPERTIES GENERATED 1)
	endforeach()

	add_library(gtest ${GOOGLETEST_SOURCES})
	include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

	set(SOURCE_EXE tests.cpp)

	add_executable(tests ${SOURCE_EXE})

	target_link_libraries(tests Binomial_heap)
	target_link_libraries(tests Binary_heap)
	target_link_libraries(tests Fibonacci_heap)
	target_link_libraries(tests gtest gtest_main)
endif()
