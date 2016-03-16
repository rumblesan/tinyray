#ifndef SHAPES_PLANE_H
#define SHAPES_PLANE_H

#include "vector.h"
#include "ray.h"

typedef struct Plane {

    Vector3D position;

    Vector3D normal;

} Plane;

Plane *plane_create(Vector3D position, Vector3D normal);

double plane_intersect(Plane *plane, Ray ray);

Vector3D plane_normal(Plane *plane, Vector3D pos);

void plane_cleanup(Plane *plane);

#endif
