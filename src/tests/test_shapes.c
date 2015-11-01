#include "tests/min_unit.h"

#include "core/shapes.h"
#include "core/coordinates.h"

static char * test_creation() {

    Coord3D centre = coord3d_create(1.0, 1.0, 1.0);
    Shape shape = shape_create(centre, 1.0);

    mu_assert("Error: Shape object not created correctly", shape->centre->x == 1);

    shape_cleanup(shape);
    coord3d_cleanup(centre);
    return 0;
}

char * test_shapes() {
    mu_run_test(test_creation);
    return 0;
}


