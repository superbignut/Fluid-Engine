cmake_minimum_required(VERSION 3.10)

set(target surface2)

project(${target})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# message("${DEFAULT_LINKER_OPTIONS}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(${target} ${sources})

target_link_libraries(${target} libbig)