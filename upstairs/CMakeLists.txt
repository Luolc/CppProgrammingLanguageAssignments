cmake_minimum_required(VERSION 3.10)
project(upstairs)

set(CMAKE_CXX_STANDARD 11)

add_executable(upstairs main.cpp big_integer.h big_integer.cpp io_util.hpp fibonacci.h fibonacci.cpp)

# copy the input sample into the binary directory
configure_file(input.txt input.txt COPYONLY)
