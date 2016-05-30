cmake_minimum_required(VERSION 3.0)
project(tinyray)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

include_directories(include)
include_directories(tracer/include)

add_subdirectory(tracer)
add_subdirectory(main)

option (WITH_TESTS "build tests" ON)

if (WITH_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
