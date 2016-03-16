#ifndef SCENE_H
#define SCENE_H

#include "canvas.h"
#include "camera.h"
#include "config.h"
#include "bclib/list.h"

typedef struct Scene {

    Canvas *canvas;
    Camera *camera;
    Config *config;

    List *lights;

    List *shapes;

} Scene;

Scene *scene_create(
    Camera *camera,
    Config *config,
    List *lights,
    List *shapes
);

void scene_cleanup(Scene *scene);

#endif

