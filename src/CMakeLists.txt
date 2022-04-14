cmake_minimum_required(VERSION ${CMAKE_REQUIRED_VERSION})

add_subdirectory(nodes)

set(PROJECT_SOURCES
        main.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${PROJECT_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE 
        NodesLib
)
