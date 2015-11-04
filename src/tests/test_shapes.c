#include "tests/min_unit.h"

#include "core/shapes.h"

static char * test_creation() {

    Shape shape = sphere_create(1.0, 2.0, 3.0, 1.0);

    mu_assert("Error: Shape object not created correctly", shape->type == SPHERE);

    shape_cleanup(shape);
    return 0;
}

char * test_shapes() {
    mu_run_test(test_creation);
    return 0;
}


