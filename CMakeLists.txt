cmake_minimum_required(VERSION 3.10)
project(ray_trace CXX)




file(GLOB SOURCES "src/*.cpp")
file(GLOB INCLUDES "include/*.hpp")

add_executable(ray ${SOURCES} ${INCLUDES})

include_directories(/usr/include)  # Adjust this path based on where headers are located
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_options(ray PRIVATE -Wall -Wextra -O3) 

set(CMAKE_BUILD_TYPE Debug)
