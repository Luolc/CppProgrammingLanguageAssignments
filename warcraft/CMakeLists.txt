cmake_minimum_required(VERSION 3.10)
project(warcraft)

set(CMAKE_CXX_STANDARD 11)

add_executable(warcraft
        main.cpp
        azeroth.cpp azeroth.h
        castle.cpp castle.h
        warrior.cpp warrior.h
        place.cpp place.h
        city.cpp city.h
        event.h event.cpp
        dragon.cpp dragon.h
        ninja.cpp ninja.h
        iceman.cpp iceman.h
        lion.cpp lion.h
        wolf.cpp wolf.h
        affiliation.h)

# copy the input samples into the binary directory
configure_file(input.txt input.txt COPYONLY)