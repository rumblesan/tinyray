#include <stdio.h>

#include "tests/min_unit.h"
#include "tests/test_coordinates.h"
#include "tests/test_shapes.h"
#include "tests/test_camera.h"

int tests_run;

int main(int argc, char *argv[]) {

    printf("\n");
    printf("*****************\n");
    printf("* Running tests *\n");
    printf("*****************\n\n");

    int result = 0;

    tests_run = 0;
    char *coord_results = test_coordinates();
    if (coord_results != 0) {
        printf("%s\n", coord_results);
    } else {
        printf("COORDINATE TESTS PASSED\n");
    }
    printf("    Tests run: %d\n", tests_run);
    printf("\n");

    result = result || (coord_results != 0);

    tests_run = 0;
    char *shape_results = test_shapes();
    if (shape_results != 0) {
        printf("%s\n", shape_results);
    } else {
        printf("SHAPE TESTS PASSED\n");
    }
    printf("    Tests run: %d\n", tests_run);
    printf("\n");

    result = result || (shape_results != 0);

    tests_run = 0;
    char *camera_results = test_camera();
    if (camera_results != 0) {
        printf("%s\n", camera_results);
    } else {
        printf("CAMERA TESTS PASSED\n");
    }
    printf("    Tests run: %d\n", tests_run);
    printf("\n");

    result = result || (camera_results != 0);

    return result;
}

