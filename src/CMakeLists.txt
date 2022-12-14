# The Flutter tooling requires that developers have CMake 3.10 or later
# installed. You should not increase this version, as doing so will cause
# the plugin to fail to compile for some customers of the plugin.
cmake_minimum_required(VERSION 3.10)

project(canvas_3d_library VERSION 0.0.1 LANGUAGES C)

set( _glad_HEADER_SEARCH_DIRS
"/usr/include"
"/usr/local/include"
"${CMAKE_SOURCE_DIR}/include")
set( _glfw3_HEADER_SEARCH_DIRS
"/usr/include"
"/usr/local/include"
"${CMAKE_SOURCE_DIR}/include")
set( _glfw3_LIB_SEARCH_DIRS
"/usr/lib"
"/usr/local/lib"
"${CMAKE_SOURCE_DIR}/lib")

# Check environment for root search directory
set( _glfw3_ENV_ROOT $ENV{GLFW3_ROOT} )
if( NOT GLFW3_ROOT AND _glfw3_ENV_ROOT )
	set(GLFW3_ROOT ${_glfw3_ENV_ROOT} )
endif()

# Put user specified location at beginning of search
if( GLAD_ROOT )
	list( INSERT _glad_HEADER_SEARCH_DIRS 0 "${GLAD_ROOT}/include" )
	list( INSERT _glad_LIB_SEARCH_DIRS 0 "${GLAD_ROOT}/lib" )
endif()

# GLAD
FIND_PATH(GLAD_INCLUDE_DIR "glad/glad.h"
PATHS ${_glad_HEADER_SEARCH_DIRS} )

if( GLFW3_ROOT )
	list( INSERT _glfw3_HEADER_SEARCH_DIRS 0 "${GLFW3_ROOT}/include" )
	list( INSERT _glfw3_LIB_SEARCH_DIRS 0 "${GLFW3_ROOT}/lib" )
endif()

# Search for the header
FIND_PATH(GLFW3_INCLUDE_DIR "GLFW/glfw3.h"
PATHS ${_glfw3_HEADER_SEARCH_DIRS} )

FIND_LIBRARY(GLFW3_LIBRARY NAMES glfw3 glfw
PATHS ${_glfw3_LIB_SEARCH_DIRS} )
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLFW3 DEFAULT_MSG
GLFW3_LIBRARY GLFW3_INCLUDE_vDIR)

link_libraries(glfw3)
link_directories(PUBLIC ${CMAKE_SOURCE_DIR}/lib)
include_directories(PUBLIC ${CMAKE_SOURCE_DIR}/include)


add_library(canvas_3d SHARED
  "canvas_3d.c"
  "glad.c"
  "engine.c"
  "engine.h"
)

set_target_properties(canvas_3d PROPERTIES
  PUBLIC_HEADER canvas_3d.h
  OUTPUT_NAME "canvas_3d"
)

target_compile_definitions(canvas_3d PUBLIC DART_SHARED_LIB)
