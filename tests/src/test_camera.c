#include "minunit.h"

#include "camera.h"
#include "vector.h"

static char * test_creation() {

    Camera *camera = camera_create(
        45,
        vector3d(1.0, 2.0, 3.0),
        vector3d(0.0, 2.0, 0.0)
    );

    mu_assert(camera->position.x == 1, "Error: Camera object not created correctly");

    camera_cleanup(camera);
    return 0;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_creation);

    return NULL;
}

RUN_TESTS(all_tests);
