#include "minunit.h"

#include "vector.h"

static char * test_creation() {

    Vector3D vector = vector3d(1.0, 1.0, 1.0);

    mu_assert(vector.x == 1, "Error: Vector3D object not created correctly");

    return 0;
}

static char * test_length() {

    Vector3D vector = vector3d(3.0, 4.0, 12.0);

    double length = vector3d_length(vector);
    mu_assert(length == 13, "Error: Vector3D length not correct");

    return 0;
}

static char * test_unit() {

    Vector3D vector = vector3d(3.0, 4.0, 0.0);

    Vector3D unit = vector3d_unit(vector);
    double newLen = vector3d_length(unit);
    mu_assert(newLen == 1, "Error: Vector3D is not unit");

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

    mu_assert(out.x ==  4, "Error: Vector3D x is not correct");
    mu_assert(out.y == -3, "Error: Vector3D y is not correct");
    mu_assert(out.z == -3, "Error: Vector3D z is not correct");

    return 0;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_creation);
    mu_run_test(test_length);
    mu_run_test(test_unit);
    mu_run_test(test_arithmatic);

    return NULL;
}

RUN_TESTS(all_tests);

