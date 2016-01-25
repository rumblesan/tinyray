#include <stdlib.h>
#include <math.h>

#include "shapes/sphere.h"

#include "vector.h"
#include "ray.h"

/* Sphere functions */
Sphere *sphere_create(Vector3D position, double radius) {
    Sphere *sphere = malloc(sizeof(Sphere));

    sphere->centre = position;
    sphere->radius = radius;

    return sphere;
}

// TODO
// This could certainly be made more efficient
double sphere_intersect(Sphere *sphere, Ray ray) {

    Vector3D origin_to_centre = vector3d_subtract(sphere->centre, ray.origin);
    // calculate length of vector from origin to a point perpendicular with
    // the centre of the circle. works because ray.direction is a unit vector
    double v = vector3d_dot(origin_to_centre, ray.direction);
    if (v < 0) {
        // sphere is behind ray
        return -1;
    }

    double ol = vector3d_length(origin_to_centre);

    double d = sqrt(pow(ol, 2) - pow(v, 2));
    if (d > sphere->radius) {
        return -1;
    }

    double diff = sqrt(pow(sphere->radius, 2) - pow(d, 2));

    return v - diff;
}

Vector3D sphere_normal(Sphere *sphere, Vector3D pos) {
    return vector3d_unit(
        vector3d_subtract(pos, sphere->centre)
    );
}

void sphere_cleanup(Sphere *sphere) {
    free(sphere);
}

