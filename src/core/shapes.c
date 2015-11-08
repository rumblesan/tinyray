#include <stdlib.h>
#include <math.h>

#include "core/shapes.h"

#include "core/vector.h"
#include "core/ray.h"
#include "core/colours.h"

double shape_intersect(Shape shape, Ray ray) {
    switch(shape->type) {
        case SPHERE: return sphere_intersect(shape->sphere, ray); break;
        case PLANE: return plane_intersect(shape->plane, ray); break;
    }
}

Vector3D shape_normal(Shape shape, Vector3D pos) {
    switch(shape->type) {
        case SPHERE: return sphere_normal(shape->sphere, pos); break;
        case PLANE: return plane_normal(shape->plane, pos); break;
    }
}

void shape_cleanup(Shape shape) {
    switch(shape->type) {
        case SPHERE: sphere_cleanup(shape->sphere); break;
        case PLANE: plane_cleanup(shape->plane); break;
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

/* Plane functions */
Shape plane_create(Vector3D position, Vector3D normal, Colour colour) {

    Shape shape = (Shape) malloc(sizeof(ShapeData));

    Plane plane = (Plane) malloc(sizeof(PlaneData));

    plane->position = position;
    plane->normal = normal;

    shape->type = PLANE;
    shape->plane = plane;
    shape->colour = colour;

    return shape;
}

double plane_intersect(Plane plane, Ray ray) {
    double n = fabs(vector3d_dot(ray.direction, plane->normal));
    if (n <= 0) {
        return -1;
    }
    Vector3D eye_to_plane = vector3d_subtract(plane->position, ray.origin);
    double d = fabs(vector3d_dot(eye_to_plane, plane->normal));
    double distance = (d / n);
    return distance;
}

Vector3D plane_normal(Plane plane, Vector3D pos) {
    return plane->normal;
}

void plane_cleanup(Plane plane) {
    free(plane);
}

