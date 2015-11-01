#include "tests/min_unit.h"

#include "core/lights.h"
#include "core/coordinates.h"

static char * test_creation() {

    Coord3D centre = coord3d_create(1.0, 1.0, 1.0);
    Light light = light_create(centre, 1.0);

    mu_assert("Error: Light object not created correctly", light->centre->x == 1);

    light_cleanup(light);
    coord3d_cleanup(centre);
    return 0;
}

char * test_lights() {
    mu_run_test(test_creation);
    return 0;
}


