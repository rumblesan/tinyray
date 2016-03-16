#include "minunit.h"

#include "lights.h"
#include "colours.h"

static char * test_creation() {

    Light *light = point_light_create(
        vector3d(1.0, 2.0, 3.0),
        1.0,
        colour(255, 255, 255)
    );

    mu_assert(light->point.position.x == 1, "Error: Light object not created correctly");

    light_destroy(light);

    return 0;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_creation);

    return NULL;
}

RUN_TESTS(all_tests);
