#ifndef SHAPES_H
#define SHAPES_H

#include "core/vector.h"
#include "core/ray.h"
#include "core/colours.h"

typedef enum {SPHERE} ShapeType;

typedef struct sphere *Sphere;
typedef struct sphere {

    Vector3D centre;

    double radius;

} SphereData;

typedef struct shape *Shape;
typedef struct shape {

    ShapeType type;

    Colour colour;

    union {
        Sphere sphere;
    };

} ShapeData;

double shape_intersect(Shape shape, Ray ray);

void shape_cleanup(Shape shape);

Vector3D shape_normal(Shape shape, Vector3D pos);

/* Sphere functions */
Shape sphere_create(double x, double y, double z, double radius, Colour colour);

double sphere_intersect(Sphere sphere, Ray ray);

Vector3D sphere_normal(Sphere sphere, Vector3D pos);

void sphere_cleanup(Sphere shape);

#endif

