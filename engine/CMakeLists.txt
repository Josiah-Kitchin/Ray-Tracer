cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Prod)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG_BUILD)
endif()

project(ray_trace_app CXX)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(ray STATIC ${SOURCES})

include_directories(./include)
include_directories(../engine/include)

target_compile_options(ray PRIVATE -Wall -Wextra -O3)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg ")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")

