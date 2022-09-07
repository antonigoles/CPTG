cmake_minimum_required(VERSION ${CMAKE_REQUIRED_VERSION})

# Collect header files
file(GLOB_RECURSE 
	HEADER_LIST
	CONFIGURE_DEPENDS
	"${PROJECT_SOURCE_DIR}/include/CPTG/nodes/*.hpp")

# Collect implementations
file(GLOB_RECURSE
	SRC_LIST
	CONFIGURE_DEPENDS
	"${PROJECT_SOURCE_DIR}/src/nodes/*.cpp")
	
	
add_library(NodesLib ${SRC_LIST} ${HEADER_LIST})

target_include_directories(NodesLib PUBLIC "${PROJECT_SOURCE_DIR}/include")

target_compile_features(NodesLib PUBLIC cxx_std_17)
