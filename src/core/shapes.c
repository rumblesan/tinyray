#include <stdlib.h>
#include <math.h>

#include "core/shapes.h"

#include "core/vector.h"
#include "core/ray.h"
#include "core/colours.h"

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
Shape sphere_create(Vector3D position, double radius, Colour colour) {

    Shape shape = (Shape) malloc(sizeof(ShapeData));

    Sphere sphere = (Sphere) malloc(sizeof(SphereData));

    sphere->centre = position;
    sphere->radius = radius;

    shape->type = SPHERE;
    shape->sphere = sphere;
    shape->colour = colour;

    return shape;
}

// TODO
// This could certainly be made more efficient
double sphere_intersect(Sphere sphere, Ray ray) {

    Vector3D origin_to_centre = vector3d_subtract(sphere->centre, ray.origin);

    // calculate length of vector from origin to a point perpendicular with
    // the centre of the circle. works because ray.direction is a unit vector
    double v = vector3d_dot(origin_to_centre, ray.direction);
    if (v < 0) {
        return -1;
    }

    double ol = vector3d_length(origin_to_centre);

    double d = sqrt(pow(ol, 2) - pow(v, 2));
    if (d > sphere->radius) {
        return -1;
    }

    double diff = sqrt(pow(d, 2) + pow(sphere->radius, 2));

    return v - diff;
}

Vector3D sphere_normal(Sphere sphere, Vector3D pos) {
    return vector3d_unit(
        vector3d_subtract(pos, sphere->centre)
    );
}

void sphere_cleanup(Sphere sphere) {
    free(sphere);
}

