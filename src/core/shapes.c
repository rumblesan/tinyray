#include <stdlib.h>
#include <math.h>

#include "core/shapes.h"
#include "core/vector.h"
#include "core/ray.h"

Shape sphere_create(double x, double y, double z, double radius) {

    Shape shape = (Shape) malloc(sizeof(ShapeData));

    Sphere sphere = (Sphere) malloc(sizeof(SphereData));

    sphere->centre = vector3d(x, y, z);
    sphere->radius = radius;

    shape->type = SPHERE;
    shape->sphere = sphere;

    return shape;
}

double shape_intersect(Shape shape, Ray ray) {
    double dist;
    switch(shape->type) {
        case SPHERE:
            dist = sphere_intersect(shape->sphere, ray);
    }
    return dist;
}

double sphere_intersect(Sphere sphere, Ray ray) {
    Vector3D eye_to_centre = vector3d_subtract(sphere->centre, ray.point);
    double v = vector3d_dot(eye_to_centre, ray.vector);
    double d = vector3d_length(eye_to_centre);
    double discriminant = (sphere->radius * sphere->radius) - d + (v * v);
    if (discriminant < 0) {
        return -1;
    } else {
        return v - sqrt(discriminant);
    }
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

