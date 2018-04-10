cmake_minimum_required(VERSION 3.8)
project(pie)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp time_limit_runner.h time_limit_runner.cpp monte_carlo_tester.h monte_carlo_tester.cpp random_generator.h random_generator.cpp)
add_executable(pie ${SOURCE_FILES})