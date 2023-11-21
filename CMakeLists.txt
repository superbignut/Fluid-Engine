cmake_minimum_required(VERSION 3.10)
project(big)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
message("CMake runtime output dir:   " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

set(EXTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external)
message("CMake external dir:   " ${EXTERNAL_DIR})

set(CMAKE_BUILD_TYPE "Debug")
message("CMake built type:  " ${CMAKE_BUILD_TYPE})

include_directories(/usr/local/include)
include_directories(include)
# include_directories(external/googletest/googletest/include)

# aux_source_directory(src source_list)

# add_executable(big ${source_list})
add_subdirectory(external/gtest EXCLUDE_FROM_ALL)
add_subdirectory(external/cnpy EXCLUDE_FROM_ALL)
add_subdirectory(external/pystring EXCLUDE_FROM_ALL)
add_subdirectory(external/flatbuffers EXCLUDE_FROM_ALL)
add_subdirectory(src/big)


add_subdirectory(src/examples/async)
add_subdirectory(src/examples/CRTP EXCLUDE_FROM_ALL)
add_subdirectory(src/examples/QA EXCLUDE_FROM_ALL)

add_subdirectory(src/test/blastest EXCLUDE_FROM_ALL)
add_subdirectory(src/test/cgtest EXCLUDE_FROM_ALL)
add_subdirectory(src/test/raytest EXCLUDE_FROM_ALL)
add_subdirectory(src/test/matrix4x4test EXCLUDE_FROM_ALL)
add_subdirectory(src/test/quaterniontest EXCLUDE_FROM_ALL)
add_subdirectory(src/test/transformtest EXCLUDE_FROM_ALL)
add_subdirectory(src/test/surface2test EXCLUDE_FROM_ALL)
add_subdirectory(src/test/sphere3test EXCLUDE_FROM_ALL)
add_subdirectory(src/test/planetest EXCLUDE_FROM_ALL)
add_subdirectory(src/test/animationtest EXCLUDE_FROM_ALL)
add_subdirectory(src/test/physics_animation_test EXCLUDE_FROM_ALL)
add_subdirectory(src/test/manual_tests)
add_subdirectory(src/test/serialtest)
# target_link_libraries(big ${OpenCV_LIBRARIES})