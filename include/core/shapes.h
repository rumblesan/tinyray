#ifndef SHAPES_H
#define SHAPES_H

#include "core/vector.h"
#include "core/ray.h"

typedef enum {SPHERE} ShapeType;

typedef struct sphere *Sphere;
typedef struct sphere {

    Vector3D centre;

    double radius;

} SphereData;

typedef struct shape *Shape;
typedef struct shape {

    ShapeType type;

    union {
        Sphere sphere;
    };

} ShapeData;

Shape sphere_create(double x, double y, double z, double radius);

double shape_intersect(Shape shape, Ray ray);

double sphere_intersect(Sphere sphere, Ray ray);

void shape_cleanup(Shape shape);

void sphere_cleanup(Sphere shape);

#endif

