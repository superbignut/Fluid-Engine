cmake_minimum_required(VERSION 3.10)
project(big)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)


include_directories(/usr/local/include) 
include_directories(include)
# include_directories(external/googletest/googletest/include)

# aux_source_directory(src source_list)

# add_executable(big ${source_list})
add_subdirectory(src/examples/async)
add_subdirectory(src/examples/CRTP)
add_subdirectory(src/test/blastest)
add_subdirectory(src/test/cgtest)
add_subdirectory(src/test/raytest)
add_subdirectory(src/test/matrix4x4test)
add_subdirectory(src/test/quaterniontest)
add_subdirectory(src/test/transformtest)
# add_executable(big src/main.cpp)
# target_link_libraries(big ${OpenCV_LIBRARIES})