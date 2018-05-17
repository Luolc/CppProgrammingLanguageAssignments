cmake_minimum_required(VERSION 3.10)
project(convex)

set(CMAKE_CXX_STANDARD 11)

add_executable(convex main.cpp point.h point.cpp line.h line.cpp io_util.hpp)

# copy the input sample into the binary directory
configure_file(input.txt input.txt COPYONLY)
