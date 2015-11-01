#ifndef SHAPES_H
#define SHAPES_H

#include "core/coordinates.h"

typedef struct shape_sphere *Shape;
typedef struct shape_sphere {

    Coord3D centre;

    double radius;

} Shape_Data;

Shape shape_create(Coord3D centre, double radius);

void shape_cleanup(Shape shape);

#endif

