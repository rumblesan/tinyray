#include "min_unit.h"

#include "camera.h"
#include "vector.h"

static char * test_creation() {

    Camera *camera = camera_create(
        45,
        vector3d(1.0, 2.0, 3.0),
        vector3d(0.0, 2.0, 0.0)
    );

    mu_assert("Error: Camera object not created correctly", camera->position.x == 1);

    camera_cleanup(camera);
    return 0;
}

char * test_camera() {
    mu_run_test(test_creation);
    return 0;
}


