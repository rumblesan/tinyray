#include <stdlib.h>

#include "scene.h"

#include "canvas.h"
#include "camera.h"
#include "config.h"
#include "collections/light_list.h"
#include "collections/shape_list.h"

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

