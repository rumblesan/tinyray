cmake_minimum_required(VERSION 3.0)
project(tinyray)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

include_directories(include)

file(GLOB_RECURSE SOURCES "src/main.c" "src/core/*.c" "src/libs/*.c")
file(GLOB_RECURSE TEST_SOURCES "src/core/*.c" "src/tests/*.c")

add_executable(tinyray ${SOURCES})
add_executable(tinyray-tests ${TEST_SOURCES})

enable_testing()
add_test(tests tinyray-tests)

