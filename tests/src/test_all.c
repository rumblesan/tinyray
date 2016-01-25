#include <stdio.h>
#include <stdbool.h>

#include "min_unit.h"
#include "test_camera.h"
#include "test_canvas.h"
#include "test_colours.h"
#include "test_config.h"
#include "test_lights.h"
#include "test_scene.h"
#include "test_shapes.h"
#include "test_tracing.h"
#include "test_vector.h"

int tests_run = 0;

bool run_test(char *test_name, char *(*test_runner)()) {
    tests_run = 0;
    printf("Running %s tests\n", test_name);
    char *test_results = test_runner();
    if (test_results != 0) {
        printf("%s\n", test_results);
    } else {
        printf("all tests passed\n");
    }
    printf("    Tests run: %d\n", tests_run);
    printf("\n");
    return (test_results != 0);
}

int main(int argc, char *argv[]) {

    printf("\n");
    printf("*****************\n");
    printf("* Running tests *\n");
    printf("*****************\n\n");

    bool camera_result     = run_test("Camera", test_camera);
    bool canvas_result     = run_test("Canvas", test_canvas);
    bool colour_result     = run_test("Colours", test_colours);
    bool config_result     = run_test("Config", test_config);
    bool lights_result     = run_test("Lights", test_lights);
    bool scene_result      = run_test("Scene", test_scene);
    bool shape_result      = run_test("Shape", test_shapes);
    bool tracing_result    = run_test("Tracing", test_tracing);
    bool vector_result     = run_test("Vector", test_vector);

    return (
        camera_result       ||
        canvas_result       ||
        colour_result       ||
        config_result       ||
        lights_result       ||
        scene_result        ||
        shape_result        ||
        tracing_result      ||
        vector_result
    );
}

