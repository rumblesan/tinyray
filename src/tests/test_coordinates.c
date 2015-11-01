#include "tests/min_unit.h"

#include "core/coordinates.h"

static char * test_creation() {

    Coord3D coord = coord3d_create(1.0, 1.0, 1.0);

    mu_assert("Error: Coord3D object not created correctly", coord->x == 1);

    coord3d_cleanup(coord);
    return 0;
}

char * test_coordinates() {
    mu_run_test(test_creation);
    return 0;
}

