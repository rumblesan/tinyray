#include "tests/min_unit.h"

#include "core/camera.h"
#include "core/vector.h"

static char * test_creation() {

    Camera camera = camera_create(
        45,
        1.0, 2.0, 3.0,
        0.0, 2.0, 0.0
    );

    mu_assert("Error: Camera object not created correctly", camera->position->x == 1);

    camera_cleanup(camera);
    return 0;
}

char * test_camera() {
    mu_run_test(test_creation);
    return 0;
}


