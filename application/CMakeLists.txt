cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Prod)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG_BUILD)
endif()

project(ray_trace_app CXX)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(ray ${SOURCES})

#source 
include_directories(./include)
include_directories(../engine/include)
target_link_directories(ray PRIVATE ${CMAKE_SOURCE_DIR}/../engine/build)
target_link_libraries(ray PRIVATE libray.a)

#for multithreading 
find_package(TBB REQUIRED)

#window
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

target_link_libraries(ray PRIVATE TBB::tbb sfml-system sfml-window sfml-graphics)

target_compile_options(ray PRIVATE -Wall -Wextra -O3)

