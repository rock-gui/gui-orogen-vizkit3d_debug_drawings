PROJECT(vizkit3d_debug_drawings)
cmake_minimum_required(VERSION 2.6)
add_definitions(-DENABLE_DEBUG_DRAWINGS)
add_definitions(-std=c++11)
SET (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/.orogen/config")
INCLUDE(vizkit3d_debug_drawingsBase)

# FIND_PACKAGE(KDL)
# FIND_PACKAGE(OCL)

