#include <stdio.h>

#include "tests/min_unit.h"

#include "tests/test_tracing.h"
#include "core/tracing.h"

#include "core/colours.h"
#include "core/scene.h"
#include "core/shapes.h"
#include "core/ray.h"
#include "core/vector.h"
#include "core/camera.h"
#include "core/config.h"

static char * test_intersection() {

    Vector3D origin = vector3d(-3.0, 4.0, 0.0);
    Vector3D looking_at = vector3d(0.0, 0.0, 0.0);
    Vector3D direction = vector3d_unit(vector3d_subtract(looking_at, origin));
    Ray r = ray(origin, direction);
    ShapeList shapes = shape_list_add(
        shape_list_create(),
        sphere_create(vector3d(0.0, 0.0, 0.0), 2.0, colour(0, 0, 0))
    );

    Intersection distObject = intersectedObject(r, shapes);

    mu_assert("Error: Intersection not happening", distObject.object != NULL);

    return 0;
}

char * test_tracing() {
    mu_run_test(test_intersection);
    return 0;
}

