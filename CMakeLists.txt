set(CMAKE_REQUIRED_VERSION 3.14)
cmake_minimum_required(VERSION ${CMAKE_REQUIRED_VERSION})

project(
	Local-CPTG 
	LANGUAGES CXX 
	VERSION 0.2.0)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	set(CMAKE_CXX_EXTENSIONS OFF)

	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

find_package(Boost 1.67.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(src/nodes)

add_subdirectory(apps)
