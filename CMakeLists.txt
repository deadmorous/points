cmake_minimum_required (VERSION 3.1.3) 
project (points_package) 

set (CMAKE_CXX_STANDARD 11)

if("${CMAKE_RUNTIME_OUTPUT_DIRECTORY}" STREQUAL "")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
message(STATUS "${PROJECT_NAME} setting CMAKE_RUNTIME_OUTPUT_DIRECTORY to ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endif()

if("${CMAKE_LIBRARY_OUTPUT_DIRECTORY}" STREQUAL "")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
message(STATUS "${PROJECT_NAME} setting CMAKE_LIBRARY_OUTPUT_DIRECTORY to ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
endif()

if("${BUILD_SHARED_LIBS}" STREQUAL "")
set (BUILD_SHARED_LIBS true)
message(STATUS "${PROJECT_NAME} setting BUILD_SHARED_LIBS to true")
endif()

# include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Svg REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5PrintSupport REQUIRED)

include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Svg_INCLUDE_DIRS})
include_directories(${Qt5Network_INCLUDE_DIRS})
include_directories(${Qt5PrintSupport_INCLUDE_DIRS})

find_package(Qt5LinguistTools REQUIRED)

add_subdirectory(src)
add_subdirectory(external/ode_num_int)
