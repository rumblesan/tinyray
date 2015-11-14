#include <stdlib.h>
#include <math.h>

#include "core/shapes/plane.h"

#include "core/vector.h"
#include "core/ray.h"

/* Plane functions */
Plane plane_create(Vector3D position, Vector3D normal) {
    Plane plane = (Plane) malloc(sizeof(PlaneData));

    plane->position = position;
    plane->normal = normal;

    return plane;
}

double plane_intersect(Plane plane, Ray ray) {
    double vd = vector3d_dot(ray.direction, plane->normal);
    double v0 = -(vector3d_dot(plane->normal, ray.origin));
    double t = v0/vd;
    if (t < 0) {
        return -1;
    } else {
        return t;
    }
}

Vector3D plane_normal(Plane plane, Vector3D pos) {
    return plane->normal;
}

void plane_cleanup(Plane plane) {
    free(plane);
}


