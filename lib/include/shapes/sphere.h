#ifndef SHAPES_SPHERE_H
#define SHAPES_SPHERE_H

#include "vector.h"
#include "ray.h"

typedef struct sphere *Sphere;
typedef struct sphere {

    Vector3D centre;

    double radius;

} SphereData;

Sphere sphere_create(Vector3D position, double radius);

double sphere_intersect(Sphere sphere, Ray ray);

Vector3D sphere_normal(Sphere sphere, Vector3D pos);

void sphere_cleanup(Sphere shape);

#endif
