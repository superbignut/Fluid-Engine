cmake_minimum_required(VERSION 3.10)
project(big)

# find_package(OpenCV REQUIRED)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(/usr/local/include) 
include_directories(include)
include_directories(external/googletest/googletest/include)

aux_source_directory(src source_list)

add_executable(big ${source_list})
# target_link_libraries(big ${OpenCV_LIBRARIES})