#include "minunit.h"

#include "shapes.h"
#include "textures.h"

static char * test_creation() {
    Texture t = texture_flat(0.5, 0, colour(0, 0, 0));
    Shape *shape = shape_sphere(vector3d(1.0, 2.0, 3.0), 1.0, t);

    mu_assert(shape->type == SPHERE, "Error: Shape object not created correctly");

    shape_cleanup(shape);
    return 0;
}

static char * test_sphere_intersect() {

    Texture t = texture_flat(0.5, 0, colour(0, 0, 0));
    Ray r = ray(
        vector3d(0.0, 0.0, 0.0), vector3d_unit(vector3d(1.0, 0.0, 0.0))
    );
    Shape *shape = shape_sphere(vector3d(4.0, 0.0, 0.0), 2.0, t);

    double distance = shape_intersect(shape, r);

    mu_assert(distance > 0,  "Error: Sphere intersection not happening");
    mu_assert(distance == 2.0, "Error: Sphere intersection distance incorrect");

    return 0;
}

static char * test_plane_intersect() {

    Texture t = texture_flat(0.5, 0, colour(0, 0, 0));
    Ray r = ray(
        vector3d(0.0, 4.0, 0.0), vector3d_unit(vector3d(0.0, -1.0, 0.0))
    );
    Shape *shape = shape_plane(
        vector3d(0.0, 0.0, 0.0),
        vector3d(0.0, 1.0, 0.0),
        t
    );

    double distance = shape_intersect(shape, r);

    mu_assert(distance > 0, "Error: Plane intersection not happening");
    mu_assert(distance == 4.0, "Error: Plane intersection distance incorrect");

    return 0;
}

static char * test_triangle_intersect() {

    Texture t = texture_flat(0.5, 0, colour(0, 0, 0));
    Ray r = ray(
        vector3d(0.0, 4.0, 0.0), vector3d_unit(vector3d(0.0, -1.0, 0.0))
    );
    Shape *shape = shape_triangle(
        vector3d(0.0,  0.0, -1.0),
        vector3d(1.0,  0.0,  1.0),
        vector3d(-1.0, 0.0,  1.0),
        t
    );

    double distance = shape_intersect(shape, r);

    mu_assert(distance > 0, "Error: Triangle intersection not happening");
    mu_assert(distance == 4.0, "Error: Triangle intersection distance incorrect");

    shape_cleanup(shape);

    return 0;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_creation);
    mu_run_test(test_sphere_intersect);
    mu_run_test(test_plane_intersect);
    mu_run_test(test_triangle_intersect);

    return NULL;
}

RUN_TESTS(all_tests);
