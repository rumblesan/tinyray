#ifndef TRACING_H
#define TRACING_H

#include "colours.h"
#include "scene.h"
#include "shapes.h"
#include "collections/shape_list.h"
#include "ray.h"

typedef struct Intersection {

    Shape *object;

    double distance;

} Intersection;

void rays_calc(Scene *scene);

Colour trace(Ray ray, Scene *scene, int depth);

Intersection intersectedObject(Ray ray, ShapeList *shapes, double max_distance);

Colour surface(Ray ray, Scene *scene, Shape *object, Vector3D intersection, int depth);

bool light_is_visible(
    Vector3D intersection,
    Light light,
    ShapeList *shapes,
    double max_distance
);

#endif
