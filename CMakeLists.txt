# Specify minimum required version of CMake
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

# Specify project and identify languages used.
project(csc305 CXX)

#include(Sanitizers.cmake)

add_library(ray_tracer ${CMAKE_SOURCE_DIR}/lib/csc305/ray_tracer.cpp)

add_subdirectory(lib/thirdparty/glm-master)
include_directories(lib/thirdparty/glm-master/glm)

# Add include DIr
target_include_directories(ray_tracer PUBLIC
                        ${CMAKE_SOURCE_DIR}/include/csc305
                        ..
                        )

# Add a program target called answer
add_executable(ray_tracer.exe app/thirdparty/ray_tracer.cpp)
target_link_libraries(ray_tracer glm)
