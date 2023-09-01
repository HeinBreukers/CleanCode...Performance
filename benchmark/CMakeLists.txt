cmake_minimum_required(VERSION 3.14)
project(bench)

include(FetchContent)

include(FetchContent)
FetchContent_Declare(googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.8.3
)

FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(googlebenchmark)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})


set(SOURCE
 benchmark.cpp
)


add_executable(${PROJECT_NAME}
      ${SOURCE}
)
target_link_libraries(${PROJECT_NAME} benchmark::benchmark)
target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wnull-dereference -Wdouble-promotion -Wformat=2)
target_include_directories(${PROJECT_NAME} PUBLIC ${googlebenchmark_SOURCE_DIR}/include)