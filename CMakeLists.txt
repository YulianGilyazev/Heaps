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
	find_package(GTest REQUIRED)
	#include_directories(${GTEST_INCLUDE_DIR})

ExternalProject_Add(
gtest
URL https://github.com/google/googletest/archive/master.zip
PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
# Disable install step
INSTALL_COMMAND ""
)

ExternalProject_Get_Property(gtest source_dir binary_dir)

add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

set_target_properties(libgtest PROPERTIES
   "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
   "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

set_target_properties(libgmock PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

include_directories("${source_dir}/googletest/include"
                "${source_dir}/googlemock/include")
	add_executable(tests test.cpp)

	target_link_libraries(tests ${GTEST_LIBRARY_DEBUG} ${GTEST_MAIN_LIBRARY_DEBUG})
        #target_link_libraries(tests ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY})

	target_link_libraries(tests Binomial_heap)
	target_link_libraries(tests Binary_heap)
	target_link_libraries(tests Fibonacci_heap)
	#target_link_libraries(tests gtest gtest_main)
	add_test( tests tests )
endif()
