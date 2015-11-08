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

    Ray r = ray(
        vector3d(-2.0, 0.0, 0.0), vector3d(-1.0, 0.0, 0.0)
    );
    ShapeList shapes = shape_list_add(
        shape_list_create(),
        sphere_create(0.0, 0.0, 0.0, 1.0)
    );

    Intersection distObject = intersectedObject(r, shapes);

    mu_assert("Error: Intersection not happening", distObject.object != NULL);
    mu_assert("Error: Intersection distance incorrect", distObject.distance == 1.0);

    return 0;
}

char * test_tracing() {
    mu_run_test(test_intersection);
    return 0;
}

