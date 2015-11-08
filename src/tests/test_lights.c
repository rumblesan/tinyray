#include "tests/min_unit.h"

#include "core/lights.h"

static char * test_creation() {

    Light light = light_create(vector3d(1.0, 2.0, 3.0), 1.0);

    mu_assert("Error: Light object not created correctly", light.position.x == 1);

    return 0;
}

char * test_lights() {
    mu_run_test(test_creation);
    return 0;
}


