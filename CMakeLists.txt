# Specify minimum required version of CMake
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

# Specify project and identify languages used.
project(csc305 CXX)

#include(Sanitizers.cmake)

add_library(ray_tracer_lib ${CMAKE_SOURCE_DIR}/lib/csc305/InputParser.cpp
                       ${CMAKE_SOURCE_DIR}/lib/csc305/Sphere.cpp
                       ${CMAKE_SOURCE_DIR}/lib/csc305/LightSource.cpp
                       ${CMAKE_SOURCE_DIR}/lib/csc305/Camera.cpp
                       ${CMAKE_SOURCE_DIR}/lib/csc305/Scene.cpp
                     )

add_subdirectory(lib/thirdparty/glm-master)
include_directories(lib/thirdparty/glm-master/glm)

# Add include DIr
target_include_directories(ray_tracer_lib PUBLIC
                        ${CMAKE_SOURCE_DIR}/include/csc305
                        ..
                        )

# Add a program target called answer
add_executable(ray_tracer app/main.cpp)
target_link_libraries(ray_tracer glm ray_tracer_lib)
