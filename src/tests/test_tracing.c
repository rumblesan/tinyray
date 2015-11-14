#include <stdio.h>

#include "tests/min_unit.h"

#include "tests/test_tracing.h"
#include "core/tracing.h"

#include "core/colours.h"
#include "core/scene.h"
#include "core/shapes.h"
#include "core/textures.h"
#include "core/ray.h"
#include "core/vector.h"
#include "core/camera.h"
#include "core/config.h"

static char * test_intersection() {

    Vector3D origin = vector3d(-3.0, 4.0, 0.0);
    Vector3D looking_at = vector3d(0.0, 0.0, 0.0);
    Vector3D direction = vector3d_unit(vector3d_subtract(looking_at, origin));
    Ray r = ray(origin, direction);
    Texture t = texture_flat(0, colour(0, 255, 255));
    ShapeList shapes = shape_list_create(
        1,
        sphere_create(vector3d(0.0, 0.0, 0.0), 2.0, t)
    );

    Intersection distObject = intersectedObject(r, shapes, 1000);

    mu_assert("Error: Intersection not happening", distObject.object != NULL);

    return 0;
}

static char * test_simple_light_visibility() {

    Vector3D intersection = vector3d(0.0, 0.0, 0.0);
    Vector3D light_pos = vector3d(0.0, 0.0, 20.0);

    Texture t = texture_flat(0, colour(0, 255, 255));
    ShapeList shapes = shape_list_create(1,
        sphere_create(vector3d(0, 0, 10), 2.0, t)
    );
    Light light = point_light_create(light_pos, 1, colour(0, 255, 255));

    bool not_visible = light_is_visible(intersection, light, shapes, 100);
    mu_assert("Error: Light should not be visible", not_visible == false);

    bool visible = light_is_visible(intersection, light, shape_list_empty(), 100);
    mu_assert("Error: Light should be visible", visible == true);

    bool visible_with_shape = light_is_visible(
        intersection,
        light,
        shape_list_create(1, sphere_create(vector3d(0, 10, 10), 2.0, t)),
        100
    );
    mu_assert("Error: Light should be visible", visible_with_shape == true);

    return 0;
}

static char * test_complex_light_visibility() {
    Vector3D intersection = vector3d(3, 0, 0);
    Vector3D light_pos = vector3d(10, 10, 0);

    Texture t = texture_flat(0, colour(0, 255, 255));
    ShapeList shapes = shape_list_create(1,
        sphere_create(vector3d(3, 4, 0), 3, t)
    );
    Light light = point_light_create(light_pos, 1, colour(0, 255, 255));

    bool not_visible = light_is_visible(intersection, light, shapes, 100);
    mu_assert("Error: Light should not be visible through sphere", not_visible == false);

    return 0;
}

char * test_tracing() {
    mu_run_test(test_intersection);
    mu_run_test(test_simple_light_visibility);
    mu_run_test(test_complex_light_visibility);
    return 0;
}

