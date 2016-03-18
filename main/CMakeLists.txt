include_directories(include)

set(SOURCES
    "src/main.c"
    "src/img_export.c"
    "src/langfuncs/tracescene.c"
    "src/libs/lodepng.c"
    )

add_executable(tinyray ${SOURCES})

set_property(TARGET tinyray PROPERTY C_STANDARD 99)

target_link_libraries(tinyray traylang-lib)
target_link_libraries(tinyray tracer-lib)
