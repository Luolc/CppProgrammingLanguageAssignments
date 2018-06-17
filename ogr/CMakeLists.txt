cmake_minimum_required(VERSION 3.10)
project(ogr)

set(CMAKE_CXX_STANDARD 11)

add_executable(ogr
        main.cpp
        string_util.hpp
        OGRGeometry.cpp OGRGeometry.h
        OGREnvelope.cpp OGREnvelope.h
        OGRPoint.cpp OGRPoint.h
        OGRSurface.cpp OGRSurface.h
        OGRCurve.cpp OGRCurve.h
        OGRSimpleCurve.cpp OGRSimpleCurve.h
        OGRLineString.cpp OGRLineString.h
        OGRLinearRing.cpp OGRLinearRing.h
        OGRGeometryCollection.cpp OGRGeometryCollection.h
        OGRMultiPoint.cpp OGRMultiPoint.h
        OGRMultiCurve.cpp OGRMultiCurve.h
        OGRMultiLineString.cpp OGRMultiLineString.h
        OGRCurvePolygon.cpp OGRCurvePolygon.h
        OGRPolygon.cpp OGRPolygon.h
        OGRMultiSurface.cpp OGRMultiSurface.h
        OGRMultiPolygon.cpp OGRMultiPolygon.h)

# copy the input samples into the binary directory
configure_file(wkt/OGRPoint_import.txt wkt/OGRPoint_import.txt COPYONLY)
configure_file(wkt/OGRPolygon_import.txt wkt/OGRPolygon_import.txt COPYONLY)
configure_file(wkt/OGRMultiPoint_import.txt wkt/OGRMultiPoint_import.txt COPYONLY)
configure_file(wkt/OGRMultiPolygon_import.txt wkt/OGRMultiPolygon_import.txt COPYONLY)