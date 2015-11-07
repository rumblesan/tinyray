#include <stdlib.h>
#include <math.h>

#include "core/shapes.h"

#include "core/vector.h"
#include "core/ray.h"

double shape_intersect(Shape shape, Ray ray) {
    switch(shape->type) {
        case SPHERE: return sphere_intersect(shape->sphere, ray);
    }
}

Vector3D shape_normal(Shape shape, Vector3D pos) {
    switch(shape->type) {
        case SPHERE: return sphere_normal(shape->sphere, pos);
    }
}

void shape_cleanup(Shape shape) {
    switch(shape->type) {
        case SPHERE: sphere_cleanup(shape->sphere);
    }
    free(shape);
}

/* Sphere functions */
Shape sphere_create(double x, double y, double z, double radius) {

    Shape shape = (Shape) malloc(sizeof(ShapeData));

    Sphere sphere = (Sphere) malloc(sizeof(SphereData));

    sphere->centre = vector3d(x, y, z);
    sphere->radius = radius;

    shape->type = SPHERE;
    shape->sphere = sphere;

    return shape;
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

Vector3D sphere_normal(Sphere sphere, Vector3D pos) {
    return vector3d_unit(
        vector3d_subtract(pos, sphere->centre)
    );
}

void sphere_cleanup(Sphere sphere) {
    free(sphere);
}

