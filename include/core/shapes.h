#ifndef SHAPES_H
#define SHAPES_H

#include "core/coordinates.h"

typedef enum {SPHERE} ShapeType;

typedef struct sphere *Sphere;
typedef struct sphere {

    Coord3D centre;

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

void shape_cleanup(Shape shape);

void sphere_cleanup(Sphere shape);

#endif

