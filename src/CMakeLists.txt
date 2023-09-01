cmake_minimum_required(VERSION 3.2)
project(example)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Union)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Variant)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Virtual)

# set(SOURCE
# examples/main.cpp

# )

# set(HEADER

# )

# add_executable(example
#       ${HEADER}
#       ${SOURCE}
# )
# target_link_libraries(example)
# target_compile_options(example PRIVATE -Werror -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wnull-dereference -Wdouble-promotion -Wformat=2)
# if GCC
#target_compile_options(SQLiteCPP PRIVATE -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wuseless-cast)
# target_include_directories(example PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/SPSCQueue)
