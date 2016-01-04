#include <stdlib.h>

#include "core/scene.h"

#include "core/canvas.h"
#include "core/camera.h"
#include "core/config.h"
#include "core/collections/light_list.h"
#include "core/collections/shape_list.h"

Scene scene_create(
    Camera camera,
    Config config,
    LightList lights,
    ShapeList shapes
) {

    Scene scene = malloc(sizeof(SceneData));

    scene->canvas = canvas_create(config->width, config->height);
    scene->camera = camera;
    scene->config = config;
    scene->lights = lights;
    scene->shapes = shapes;

    return scene;
}

void scene_cleanup(Scene scene) {
    canvas_cleanup(scene->canvas);
    camera_cleanup(scene->camera);
    config_cleanup(scene->config);
    light_list_cleanup(scene->lights);
    shape_list_cleanup(scene->shapes);
    free(scene);
}

