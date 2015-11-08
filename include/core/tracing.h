#ifndef TRACING_H
#define TRACING_H

#include "core/colours.h"
#include "core/scene.h"
#include "core/shapes.h"
#include "core/collections/shape_list.h"
#include "core/ray.h"

typedef struct intersection {

    Shape object;

    double distance;

} Intersection;

void rays_calc(Scene scene);

Colour trace(Ray ray, Scene scene, int depth);

Intersection intersectedObject(Ray ray, ShapeList shapes, double max_distance);

Colour surface(Ray ray, Scene scene, Shape object, Vector3D intersection, int depth);

bool light_is_visible(Vector3D intersection, Scene scene, Light light);

#endif
