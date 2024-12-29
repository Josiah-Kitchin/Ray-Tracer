cmake_minimum_required(VERSION 3.10)
project(ray_trace CXX)

file(GLOB SOURCES "src/*.cpp")
file(GLOB INCLUDES "include/*.hpp")

add_executable(ray ${SOURCES} ${INCLUDES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(TBB REQUIRED)

target_link_libraries(ray PRIVATE TBB::tbb)

target_compile_options(ray PRIVATE -Wall -Wextra -O3)

set(CMAKE_BUILD_TYPE Debug)
