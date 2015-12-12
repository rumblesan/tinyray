#include "tests/min_unit.h"

#include "core/vector.h"
#include "tests/test_vector.h"

static char * test_creation() {

    Vector3D vector = vector3d(1.0, 1.0, 1.0);

    mu_assert("Error: Vector3D object not created correctly", vector.x == 1);

    return 0;
}

static char * test_length() {

    Vector3D vector = vector3d(3.0, 4.0, 12.0);

    double length = vector3d_length(vector);
    mu_assert("Error: Vector3D length not correct", length == 13);

    return 0;
}

static char * test_unit() {

    Vector3D vector = vector3d(3.0, 4.0, 0.0);

    Vector3D unit = vector3d_unit(vector);
    double newLen = vector3d_length(unit);
    mu_assert("Error: Vector3D is not unit", newLen == 1);

    return 0;
}

static char * test_arithmatic() {

    Vector3D vector1 = vector3d(1.0, 4.0, 2.0);
    Vector3D vector2 = vector3d(3.0, 1.0, 2.0);
    Vector3D vector3 = vector3d(3.0, 4.0, -1.0);
    Vector3D out     = vector3d_subtract(
        vector3d_add(vector2, vector3),
        vector3d_scale(2, vector1)
    );

    mu_assert("Error: Vector3D x is not correct", out.x == 4);
    mu_assert("Error: Vector3D y is not correct", out.y == -3);
    mu_assert("Error: Vector3D z is not correct", out.z == -3);

    return 0;
}

char * test_vector() {
    mu_run_test(test_creation);
    mu_run_test(test_length);
    mu_run_test(test_unit);
    mu_run_test(test_arithmatic);
    return 0;
}

