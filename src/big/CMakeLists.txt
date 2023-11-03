cmake_minimum_required(VERSION 3.10)

set(target libbig)

project(${target})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set(root_dir ${CMAKE_CURRENT_SOURCE_DIR})
# message("${BUILD_SHARED_LIBS}")

file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(${target} ${sources})
