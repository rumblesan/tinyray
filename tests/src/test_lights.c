#include "min_unit.h"

#include "lights.h"
#include "colours.h"

static char * test_creation() {

    Light *light = point_light_create(
        vector3d(1.0, 2.0, 3.0),
        1.0,
        colour(255, 255, 255)
    );

    mu_assert("Error: Light object not created correctly", light->point.position.x == 1);

    light_destroy(light);

    return 0;
}

char * test_lights() {
    mu_run_test(test_creation);
    return 0;
}


