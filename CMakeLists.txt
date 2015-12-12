cmake_minimum_required(VERSION 3.0)
project(tinyray)

include_directories(include)

file(GLOB SOURCES "src/core/**/*.c" "src/main.c" "src/libs/**/*.c")

add_executable(tinyray ${SOURCES})

