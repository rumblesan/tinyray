include_directories(include)

file(GLOB_RECURSE TEST_SOURCES "src/*.c")
set(TEST_SOURCES
    "src/test_camera.c"
    "src/test_canvas.c"
    "src/test_colours.c"
    "src/test_config.c"
    "src/test_lights.c"
    "src/test_scene.c"
    "src/test_shapes.c"
    "src/test_tracing.c"
    "src/test_vector.c"
    )

foreach(TEST_FILE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    add_executable("tinyray_${TEST_NAME}" ${TEST_FILE})
    target_link_libraries("tinyray_${TEST_NAME}" tracer-lib)
    add_test("${TEST_NAME}s" "tinyray_${TEST_NAME}")
endforeach(TEST_FILE)

