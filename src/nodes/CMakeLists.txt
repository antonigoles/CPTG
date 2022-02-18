cmake_minimum_required(VERSION ${CMAKE_REQUIRED_VERSION})

set(NODE_SOURCES
    Object.hpp
    Seq.hpp
    Seq.cpp)

add_library(NodesLib STATIC ${NODE_SOURCES})
