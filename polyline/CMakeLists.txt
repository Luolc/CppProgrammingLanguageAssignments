cmake_minimum_required(VERSION 3.10)
project(polyline)

set(CMAKE_CXX_STANDARD 11)

add_executable(polyline main.cpp io_util.hpp polyline.h polyline.cpp point.h point.cpp line.h line.cpp)

# copy the input sample into the binary directory
configure_file(input.txt input.txt COPYONLY)
