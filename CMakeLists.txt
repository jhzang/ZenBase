project(ZENBASE CXX)
cmake_minimum_required(VERSION 2.8)

message(STATUS "Build Type: " ${CMAKE_BUILD_TYPE})

add_subdirectory(src lib)
add_subdirectory(test test EXCLUDE_FROM_ALL)

