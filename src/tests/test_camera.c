#include "tests/min_unit.h"

#include "core/camera.h"
#include "core/coordinates.h"

static char * test_creation() {

    Coord3D position = coord3d_create(1.0, 1.0, 1.0);
    Coord3D looking_at = coord3d_create(0.0, 0.0, 0.0);

    Camera camera = camera_create(position, looking_at);

    mu_assert("Error: Camera object not created correctly", camera->position->x == 1);

    camera_cleanup(camera);
    coord3d_cleanup(position);
    coord3d_cleanup(looking_at);
    return 0;
}

char * test_camera() {
    mu_run_test(test_creation);
    return 0;
}


