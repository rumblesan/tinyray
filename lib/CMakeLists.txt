include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.c")
add_library(tinyray-lib SHARED ${SOURCES})

