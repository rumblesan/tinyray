#include <stdio.h>

#include "tests/min_unit.h"

#include "core/shapes.h"

static char * test_creation() {

    Shape shape = sphere_create(1.0, 2.0, 3.0, 1.0);

    mu_assert("Error: Shape object not created correctly", shape->type == SPHERE);

    shape_cleanup(shape);
    return 0;
}

static char * test_intersect() {

    Ray r = ray(
        vector3d(0.0, 0.0, 0.0), vector3d(1.0, 0.0, 0.0)
    );
    Shape shape = sphere_create(2.0, 0.0, 0.0, 1.0);

    double distance = shape_intersect(shape, r);

    mu_assert("Error: Intersection not happening", distance > 0);
    mu_assert("Error: Intersection distance incorrect", distance == 1.0);

    return 0;
}

char * test_shapes() {
    printf("Running shape tests\n");
    mu_run_test(test_creation);
    mu_run_test(test_intersect);
    return 0;
}


