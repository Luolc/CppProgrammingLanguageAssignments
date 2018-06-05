cmake_minimum_required(VERSION 3.10)
project(dosgis)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(gis_shape)
include_directories(graphics)
include_directories(util)

add_executable(dosgis
        gis_shape/abstract_gis_shape.cpp
        gis_shape/abstract_gis_shape.h
        gis_shape/gis_point.cpp
        gis_shape/gis_point.h
        gis_shape/gis_polygon.cpp
        gis_shape/gis_polygon.h
        gis_shape/gis_polyline.cpp
        gis_shape/gis_polyline.h
        gis_shape/gis_ring.cpp
        gis_shape/gis_ring.h
        gis_shape/gis_shape_set.h
        graphics/line.cpp
        graphics/line.h
        graphics/point.cpp
        graphics/point.h
        util/io_util.hpp
        util/string_util.hpp
        dos_gis.cpp
        dos_gis.h
        main.cpp)

# copy the input sample into the binary directory
configure_file(input.txt input.txt COPYONLY)
