cmake_minimum_required(VERSION 3.0)
project(tinyray)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

include_directories(include)

file(GLOB_RECURSE SOURCES "src/core/*.c" "src/libs/*.c")

add_executable(tinyray "src/main.c" ${SOURCES})

enable_testing()
file(GLOB_RECURSE TEST_SOURCES "tests/src/*.c")
add_executable(tinyray-tests ${SOURCES} ${TEST_SOURCES})
add_test(tests tinyray-tests)

