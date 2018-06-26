cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

add_library(slicer_core SHARED librarySlicerCore.cpp librarySlicerCore.h configManager.cpp configManager.h slicerUtils.h filter.h
        filter.cpp SlicerCore.cpp SlicerCore.h FilterRender.cpp FilterRender.h Point.h Geometry.cpp Geometry.h Point.cpp)
