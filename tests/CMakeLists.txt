cmake_minimum_required(VERSION 3.10)
project(Testing CXX)


# Specify source files
file(GLOB SOURCES "../src/*.cpp")
file(GLOB INCLUDES "../include/*.hpp") 
list(FILTER SOURCES EXCLUDE REGEX "main.cpp$")

file(GLOB TEST_SOURCES "*.cpp") 


set(GTEST_DIR ./googletest)  # Specify the path to Google Test
add_subdirectory(${GTEST_DIR} gtest)

# Create executable
add_executable(ray_test ${SOURCES} ${INCLUDES} ${TEST_SOURCES})

# Include directories
include_directories(/usr/include)  # Adjust this path based on where headers are located
#include_directories(../../include) 
include_directories(../include) 


# Link libraries
target_link_libraries(ray_test PRIVATE 
    gtest
    gtest_main
)

# Compiler options
target_compile_options(ray_test PRIVATE -Wall -Wextra -g) 

# Build configuration
set(CMAKE_BUILD_TYPE Debug)



