cmake_minimum_required(VERSION 3.10)

set(target serialtest)

project(${target})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# message("${DEFAULT_LINKER_OPTIONS}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${EXTERNAL_DIR}/gtest/googletest/include
                    ${EXTERNAL_DIR}/gtest/googlemock/include)

file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(${target} ${sources})

target_link_libraries(${target} 
                        libbig
                        gtest
                        gmock)