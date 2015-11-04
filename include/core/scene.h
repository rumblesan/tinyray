#ifndef SCENE_H
#define SCENE_H

#include "core/canvas.h"
#include "core/camera.h"
#include "core/config.h"
#include "core/lights.h"
#include "core/light_list.h"
#include "core/shapes.h"
#include "core/shape_list.h"

typedef struct scene *Scene;
typedef struct scene {

    Canvas canvas;
    Camera camera;
    Config config;

    LightList lights;

    ShapeList shapes;

} SceneData;

Scene scene_create(
    Canvas canvas,
    Camera camera,
    Config config,
    LightList lights,
    ShapeList shapes
);

void scene_cleanup(Scene scene);

#endif

