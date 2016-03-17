#include <stdlib.h>
#include <stdio.h>

#include "scene.h"

#include "canvas.h"
#include "camera.h"
#include "config.h"
#include "bclib/list.h"

Scene *scene_create(
    Camera *camera,
    Config *config,
    List *lights,
    List *shapes
) {

    Scene *scene = malloc(sizeof(Scene));

    scene->canvas = canvas_create(config->width, config->height);
    scene->camera = camera;
    scene->config = config;
    scene->lights = lights;
    scene->shapes = shapes;

    return scene;
}

void scene_cleanup(Scene *scene) {
    canvas_cleanup(scene->canvas);
    camera_cleanup(scene->camera);
    config_cleanup(scene->config);
    list_destroy(scene->lights);
    list_destroy(scene->shapes);
    free(scene);
}

