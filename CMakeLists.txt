cmake_minimum_required(VERSION 3.6)
project(proj4a)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES test5.cpp NoCopyString.cpp MinMaxHeap.cpp MinMaxHeap.h )
add_executable(proj4a ${SOURCE_FILES})