#ifndef SCENE_H
#define SCENE_H

#include "canvas.h"
#include "camera.h"
#include "config.h"
#include "collections/light_list.h"
#include "collections/shape_list.h"

typedef struct Scene {

    Canvas *canvas;
    Camera *camera;
    Config *config;

    LightList *lights;

    ShapeList *shapes;

} Scene;

Scene *scene_create(
    Camera *camera,
    Config *config,
    LightList *lights,
    ShapeList *shapes
);

void scene_cleanup(Scene *scene);

#endif

