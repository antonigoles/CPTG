cmake_minimum_required(VERSION ${CMAKE_REQUIRED_VERSION})

# Collect header files
file(GLOB_RECURSE 
	HEADER_LIST
	CONFIGURE_DEPENDS
	"${PROJECT_SOURCE_DIR}/include/CPTG/printers/*.hpp")

# Collect implementations
file(GLOB_RECURSE
	SRC_LIST
	CONFIGURE_DEPENDS
	"${PROJECT_SOURCE_DIR}/src/printers/*.cpp")
	
	
add_library(PrintersLib ${SRC_LIST} ${HEADER_LIST})

target_include_directories(PrintersLib PUBLIC "${PROJECT_SOURCE_DIR}/include")

target_compile_features(PrintersLib PUBLIC cxx_std_17)
