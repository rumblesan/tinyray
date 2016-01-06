include_directories(include)

file(GLOB_RECURSE MAIN_SOURCES "src/main.c" "src/libs/*.c")

add_executable(tinyray ${MAIN_SOURCES})

set_property(TARGET tinyray PROPERTY C_STANDARD 99)

target_link_libraries(tinyray tinyray-lib)
