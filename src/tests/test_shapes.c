#include "tests/min_unit.h"

#include "core/shapes.h"
#include "core/textures.h"

static char * test_creation() {
    Texture t = texture_flat(0.5, 0, colour(0, 0, 0));
    Shape shape = shape_sphere(vector3d(1.0, 2.0, 3.0), 1.0, t);

    mu_assert("Error: Shape object not created correctly", shape->type == SPHERE);

    shape_cleanup(shape);
    return 0;
}

static char * test_sphere_intersect() {

    Texture t = texture_flat(0.5, 0, colour(0, 0, 0));
    Ray r = ray(
        vector3d(0.0, 0.0, 0.0), vector3d_unit(vector3d(1.0, 0.0, 0.0))
    );
    Shape shape = shape_sphere(vector3d(4.0, 0.0, 0.0), 2.0, t);

    double distance = shape_intersect(shape, r);

    mu_assert("Error: Sphere intersection not happening", distance > 0);
    mu_assert("Error: Sphere intersection distance incorrect", distance == 2.0);

    return 0;
}

static char * test_plane_intersect() {

    Texture t = texture_flat(0.5, 0, colour(0, 0, 0));
    Ray r = ray(
        vector3d(0.0, 4.0, 0.0), vector3d_unit(vector3d(0.0, -1.0, 0.0))
    );
    Shape shape = shape_plane(
        vector3d(0.0, 0.0, 0.0),
        vector3d(0.0, 1.0, 0.0),
        t
    );

    double distance = shape_intersect(shape, r);

    mu_assert("Error: Plane intersection not happening", distance > 0);
    mu_assert("Error: Plane intersection distance incorrect", distance == 4.0);

    return 0;
}

char * test_shapes() {
    mu_run_test(test_creation);
    mu_run_test(test_sphere_intersect);
    mu_run_test(test_plane_intersect);
    return 0;
}


