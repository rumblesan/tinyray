#include <stdlib.h>
#include <math.h>

#include "core/shapes.h"
#include "core/coordinates.h"

Shape shape_create(Coord3D centre, double radius) {

    Shape sphere = (Shape) malloc(sizeof(Shape_Data));

    sphere->centre = centre;
    sphere->radius = radius;

    return sphere;
}

void shape_cleanup(Shape shape) {
    free(shape);
}


