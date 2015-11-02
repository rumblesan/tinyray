#include <stdlib.h>
#include <math.h>

#include "core/shapes.h"
#include "core/coordinates.h"

Shape sphere_create(double x, double y, double z, double radius) {

    Shape shape = (Shape) malloc(sizeof(Shape_Data));

    Sphere sphere = (Sphere) malloc(sizeof(Sphere_Data));

    sphere->centre = coord3d_create(x, y, z);
    sphere->radius = radius;

    shape->type = SPHERE;
    shape->sphere = sphere;

    return shape;
}

void shape_cleanup(Shape shape) {
    switch(shape->type) {
        case SPHERE: sphere_cleanup(shape->sphere);
    }
    free(shape);
}

void sphere_cleanup(Sphere sphere) {
    coord3d_cleanup(sphere->centre);
    free(sphere);
}

