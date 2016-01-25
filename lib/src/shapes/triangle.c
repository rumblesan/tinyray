#include <stdlib.h>
#include <math.h>

#include "constants.h"

#include "shapes/triangle.h"

#include "vector.h"
#include "ray.h"

/* Triangle functions */
Triangle *triangle_create(Vector3D point1, Vector3D point2, Vector3D point3) {
    Triangle *triangle = malloc(sizeof(Triangle));

    triangle->point1 = point1;
    triangle->point2 = point2;
    triangle->point3 = point3;

    Vector3D e1 = vector3d_subtract(point2, point1);
    Vector3D e2 = vector3d_subtract(point3, point1);
    triangle->normal = vector3d_cross(e2, e1);

    return triangle;
}

double triangle_intersect(Triangle *triangle, Ray ray) {

    Vector3D e1, e2, P, Q, T;
    double det, inv_det, u, v, t;

    e1 = vector3d_subtract(triangle->point2, triangle->point1);
    e2 = vector3d_subtract(triangle->point3, triangle->point1);

    P = vector3d_cross(ray.direction, e2);
    det = vector3d_dot(e1, P);

    if (det > -LIMINALITY && det < LIMINALITY) return -1;
    inv_det = 1.0 / det;

    T = vector3d_subtract(ray.origin, triangle->point1);

    u = vector3d_dot(T, P) * inv_det;
    if (u < 0.0 || u > 1.0) return -1;

    Q = vector3d_cross(T, e1);

    v = vector3d_dot(ray.direction, Q) * inv_det;
    if (v < 0.0 || u + v > 1.0) return -1;

    t = vector3d_dot(e2, Q) * inv_det;

    if (t > LIMINALITY) {
        return t;
    }

    return -1;

}

Vector3D triangle_normal(Triangle *triangle, Vector3D pos) {
    return triangle->normal;
}

void triangle_cleanup(Triangle *triangle) {
    free(triangle);
}



