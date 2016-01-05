cmake_minimum_required(VERSION 3.0)
project(tinyray)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

include_directories(include)

file(GLOB_RECURSE SOURCES "src/core/*.c" "src/libs/*.c")

add_executable(tinyray "src/main.c" ${SOURCES})

set_property(TARGET tinyray PROPERTY C_STANDARD 99)

option (WITH_TESTS "build tests" ON)

if (WITH_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
