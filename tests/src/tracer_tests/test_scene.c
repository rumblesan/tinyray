#include "minunit.h"

#include "canvas.h"
#include "camera.h"
#include "config.h"
#include "lights.h"
#include "scene.h"
#include "shapes.h"
#include "textures.h"
#include "bclib/list.h"

static char * test_creation() {

    Colour background = colour(0, 100, 100);

    Camera *camera = camera_create(
        45,
        vector3d(1.0, 0.0, 2.0),
        vector3d(0.0, 0.0, 0.0)
    );
    Config *config = config_create(640, 480, 1000, 10, background);
    Light *light = point_light_create(
        vector3d(1.0, 2.0, 3.0),
        1.0,
        colour(255, 255, 255)
    );
    List *lights = list_create();
    list_unshift(lights, light);
    Texture t = texture_flat(0.5, 0, colour(0, 0, 0));
    Shape *shape = shape_sphere(
        vector3d(1.0, 2.0, 3.0),
        1.0,
        t
    );
    List *shapes = list_create();
    list_unshift(shapes, shape);

    Scene *scene = scene_create(
        camera,
        config,
        lights,
        shapes
    );

    mu_assert(scene->config->width == 640, "Error: Scene object not created correctly");

    scene_cleanup(scene);
    return 0;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_creation);

    return NULL;
}

RUN_TESTS(all_tests);
