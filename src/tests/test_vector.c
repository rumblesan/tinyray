#include "tests/min_unit.h"

#include "core/vector.h"
#include "tests/test_vector.h"

static char * test_creation() {

    Vector3D vector = vector3d_create(1.0, 1.0, 1.0);

    mu_assert("Error: Vector3D object not created correctly", vector->x == 1);

    vector3d_cleanup(vector);
    return 0;
}

char * test_vector() {
    mu_run_test(test_creation);
    return 0;
}

