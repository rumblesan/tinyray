include_directories(include)

set(TRACER_TEST_SOURCES
    "src/tracer/test_camera.c"
    "src/tracer/test_canvas.c"
    "src/tracer/test_colours.c"
    "src/tracer/test_config.c"
    "src/tracer/test_lights.c"
    "src/tracer/test_scene.c"
    "src/tracer/test_shapes.c"
    "src/tracer/test_tracing.c"
    "src/tracer/test_vector.c"
    )

foreach(TEST_FILE ${TRACER_TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    add_executable("tracer_${TEST_NAME}" ${TEST_FILE})
    target_link_libraries("tracer_${TEST_NAME}" tracer-lib)
    add_test("tracer_${TEST_NAME}" "tracer_${TEST_NAME}")
endforeach(TEST_FILE)

