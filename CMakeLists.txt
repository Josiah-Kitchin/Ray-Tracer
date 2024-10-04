cmake_minimum_required(VERSION 3.10)
project(ray_trace CXX)




file(GLOB SOURCES "src/*.cpp")
file(GLOB INCLUDES "include/*.hpp")

add_executable(ray ${SOURCES} ${INCLUDES})

# Include directories
include_directories(/usr/include)  # Adjust this path based on where headers are located
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link libraries
# target_link_libraries(ray PRIVATE )

# Compiler options
target_compile_options(ray PRIVATE -Wall -Wextra -g) 

# Build configuration
set(CMAKE_BUILD_TYPE Debug)
