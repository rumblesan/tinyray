#include <stdio.h>

#include "minunit.h"

#include "tracing.h"

#include "colours.h"
#include "scene.h"
#include "shapes.h"
#include "textures.h"
#include "ray.h"
#include "vector.h"
#include "camera.h"
#include "config.h"

static char * test_intersection() {

    Vector3D origin = vector3d(-3.0, 4.0, 0.0);
    Vector3D looking_at = vector3d(0.0, 0.0, 0.0);
    Vector3D direction = vector3d_unit(vector3d_subtract(looking_at, origin));
    Ray r = ray(origin, direction);
    Texture t = texture_flat(0, 0, colour(0, 255, 255));
    List *shapes = list_create();
    list_push(shapes,
        shape_sphere(vector3d(0.0, 0.0, 0.0), 2.0, t)
    );

    Intersection distObject = intersectedObject(r, shapes, 1000);

    mu_assert(distObject.object != NULL, "Error: Intersection not happening");

    return 0;
}

static char * test_simple_light_visibility() {

    Vector3D intersection = vector3d(0.0, 0.0, 0.0);
    Vector3D light_pos = vector3d(0.0, 0.0, 20.0);

    Texture t = texture_flat(0, 0, colour(0, 255, 255));
    List *shapes = list_create();
    list_push(shapes,
        shape_sphere(vector3d(0, 0, 10), 2.0, t)
    );
    Light *light = point_light_create(light_pos, 1, colour(0, 255, 255));

    bool not_visible = light_is_visible(intersection, light, shapes, 100);
    mu_assert(not_visible == false, "Error: Light should not be visible");

    bool visible = light_is_visible(intersection, light, list_create(), 100);
    mu_assert(visible == true, "Error: Light should be visible");

    bool visible_with_shape = light_is_visible(
        intersection,
        light,
        list_push(list_create(), shape_sphere(vector3d(0, 10, 10), 2.0, t)),
        100
    );
    mu_assert(visible_with_shape == true, "Error: Light should be visible");

    return 0;
}

static char * test_complex_light_visibility() {
    Vector3D intersection = vector3d(3, 0, 0);
    Vector3D light_pos = vector3d(10, 10, 0);

    Texture t = texture_flat(0, 0, colour(0, 255, 255));
    List *shapes = list_create();
    list_push(shapes,
        shape_sphere(vector3d(3, 4, 0), 3, t)
    );
    Light *light = point_light_create(light_pos, 1, colour(0, 255, 255));

    bool not_visible = light_is_visible(intersection, light, shapes, 100);
    mu_assert(not_visible == false, "Error: Light should not be visible through sphere");

    return 0;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_intersection);
    mu_run_test(test_simple_light_visibility);
    mu_run_test(test_complex_light_visibility);

    return NULL;
}

RUN_TESTS(all_tests);

