#include <stdlib.h>
#include <math.h>

#include "core/shapes.h"
#include "core/shapes/sphere.h"
#include "core/shapes/plane.h"
#include "core/shapes/triangle.h"

#include "core/vector.h"
#include "core/ray.h"
#include "core/textures.h"

Shape shape_sphere(Vector3D position, double radius, Texture texture) {
    Sphere sphere = sphere_create(position, radius);

    Shape shape = malloc(sizeof(ShapeData));

    shape->type = SPHERE;
    shape->sphere = sphere;
    shape->texture = texture;

    return shape;
}

Shape shape_plane(Vector3D position, Vector3D normal, Texture texture) {

    Plane plane = plane_create(position, normal);

    Shape shape = malloc(sizeof(ShapeData));

    shape->type = PLANE;
    shape->plane = plane;
    shape->texture = texture;

    return shape;
}

Shape shape_triangle(
    Vector3D point1,
    Vector3D point2,
    Vector3D point3,
    Texture texture
) {

    Triangle triangle = triangle_create(point1, point2, point3);

    Shape shape = malloc(sizeof(ShapeData));

    shape->type = TRIANGLE;
    shape->triangle = triangle;
    shape->texture = texture;

    return shape;
}

double shape_intersect(Shape shape, Ray ray) {
    switch(shape->type) {
        case SPHERE: return sphere_intersect(shape->sphere, ray); break;
        case PLANE: return plane_intersect(shape->plane, ray); break;
        case TRIANGLE: return triangle_intersect(shape->triangle, ray); break;
    }
}

Vector3D shape_normal(Shape shape, Vector3D pos) {
    switch(shape->type) {
        case SPHERE: return sphere_normal(shape->sphere, pos); break;
        case PLANE: return plane_normal(shape->plane, pos); break;
        case TRIANGLE: return triangle_normal(shape->triangle, pos); break;
    }
}

void shape_cleanup(Shape shape) {
    switch(shape->type) {
        case SPHERE: sphere_cleanup(shape->sphere); break;
        case PLANE: plane_cleanup(shape->plane); break;
        case TRIANGLE: triangle_cleanup(shape->triangle); break;
    }
    free(shape);
}

