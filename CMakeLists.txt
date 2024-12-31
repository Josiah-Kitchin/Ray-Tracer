cmake_minimum_required(VERSION 3.10)
project(ray_trace CXX)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(ray ${SOURCES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(TBB REQUIRED)

target_link_libraries(ray PRIVATE TBB::tbb)

target_compile_options(ray PRIVATE -Wall -Wextra -O3)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")

set(CMAKE_BUILD_TYPE Debug)
