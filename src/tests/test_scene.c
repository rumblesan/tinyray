#include "tests/min_unit.h"
#include "tests/test_scene.h"

#include "core/canvas.h"
#include "core/camera.h"
#include "core/config.h"
#include "core/lights.h"
#include "core/scene.h"
#include "core/shapes.h"
#include "core/collections/light_list.h"
#include "core/collections/shape_list.h"

static char * test_creation() {

    Colour background = colour(0, 100, 100);

    Camera camera = camera_create(
        45,
        vector3d(1.0, 0.0, 2.0),
        vector3d(0.0, 0.0, 0.0)
    );
    Config config = config_create(640, 480, 1000, background);
    Light light = light_create(vector3d(1.0, 2.0, 3.0), 1.0);
    LightList lights = light_list_add(light_list_create(), light);
    Shape shape = sphere_create(
        vector3d(1.0, 2.0, 3.0),
        1.0,
        colour(0, 0, 0)
    );
    ShapeList shapes = shape_list_create(1, shape);

    Scene scene = scene_create(
        camera,
        config,
        lights,
        shapes
    );

    mu_assert("Error: Scene object not created correctly", scene->config->width == 640);

    scene_cleanup(scene);
    return 0;
}

char * test_scene() {
    mu_run_test(test_creation);
    return 0;
}

