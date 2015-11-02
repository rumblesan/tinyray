#include <stdio.h>

#include "tests/min_unit.h"
#include "tests/test_coordinates.h"
#include "tests/test_shapes.h"
#include "tests/test_shape_list.h"
#include "tests/test_camera.h"
#include "tests/test_config.h"
#include "tests/test_lights.h"
#include "tests/test_light_list.h"

int tests_run = 0;

int run_test(char *test_name, char *(*test_runner)()) {
    tests_run = 0;
    char *test_results = test_runner();
    if (test_results != 0) {
        printf("%s\n", test_results);
    } else {
        printf("%s tests passed\n", test_name);
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

    int coord_result  = run_test("Coordinates", test_coordinates);
    int shape_result  = run_test("Shape", test_shapes);
    int shape_list_result  = run_test("ShapeList", test_shape_list);
    int camera_result = run_test("Camera", test_camera);
    int config_result = run_test("Config", test_config);
    int lights_result = run_test("Lights", test_lights);
    int light_list_result = run_test("LightList", test_light_list);

    return (
        coord_result        ||
        shape_result        ||
        shape_list_result   ||
        camera_result       ||
        config_result       ||
        lights_result       ||
        light_list_result
    );
}

