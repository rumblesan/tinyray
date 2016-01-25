#include "min_unit.h"
#include "test_scene.h"

#include "canvas.h"
#include "camera.h"
#include "config.h"
#include "lights.h"
#include "scene.h"
#include "shapes.h"
#include "textures.h"
#include "collections/light_list.h"
#include "collections/shape_list.h"

static char * test_creation() {

    Colour background = colour(0, 100, 100);

    Camera *camera = camera_create(
        45,
        vector3d(1.0, 0.0, 2.0),
        vector3d(0.0, 0.0, 0.0)
    );
    Config *config = config_create(640, 480, 1000, 10, background);
    Light light = point_light_create(
        vector3d(1.0, 2.0, 3.0),
        1.0,
        colour(255, 255, 255)
    );
    LightList *lights = light_list_create(1, light);
    Texture t = texture_flat(0.5, 0, colour(0, 0, 0));
    Shape *shape = shape_sphere(
        vector3d(1.0, 2.0, 3.0),
        1.0,
        t
    );
    ShapeList *shapes = shape_list_create(1, shape);

    Scene *scene = scene_create(
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

