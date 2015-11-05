#include <stdlib.h>
#include <math.h>

#include "core/shapes.h"
#include "core/vector.h"

Shape sphere_create(double x, double y, double z, double radius) {

    Shape shape = (Shape) malloc(sizeof(ShapeData));

    Sphere sphere = (Sphere) malloc(sizeof(SphereData));

    sphere->centre = vector3d(x, y, z);
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
    free(sphere);
}

