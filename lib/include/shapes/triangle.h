#ifndef SHAPES_TRIANGLE_H
#define SHAPES_TRIANGLE_H

#include "vector.h"
#include "ray.h"

typedef struct Triangle {

    Vector3D point1;
    Vector3D point2;
    Vector3D point3;

    Vector3D normal;

} Triangle;

Triangle *triangle_create(Vector3D point1, Vector3D point2, Vector3D point3);

double triangle_intersect(Triangle *triangle, Ray ray);

Vector3D triangle_normal(Triangle *triangle, Vector3D pos);

void triangle_cleanup(Triangle *triangle);

#endif

