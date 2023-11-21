cmake_minimum_required(VERSION 3.10)

set(target libbig)


set(root_dir ${CMAKE_CURRENT_SOURCE_DIR}/../..)

project(${target})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(${target} ${sources})

# The flatbuffers target carry header search path automatically if CMake > 2.8.11.
target_link_libraries(${target} PRIVATE flatbuffers)

# target_include_directories(${target} PRIVATE ${root_dir}/external/flatbuffers/include)

