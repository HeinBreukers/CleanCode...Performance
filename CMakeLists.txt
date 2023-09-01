cmake_minimum_required(VERSION 3.2)

project(CleanCode...Performance)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/CLike)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/Union)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/Variant)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/Virtual)

# add_subdirectory(src)
add_subdirectory(benchmark)


