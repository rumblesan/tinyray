#ifndef SHAPES_H
#define SHAPES_H

#include "vector.h"
#include "ray.h"
#include "textures.h"

#include "shapes/sphere.h"
#include "shapes/plane.h"
#include "shapes/triangle.h"

typedef enum {SPHERE, PLANE, TRIANGLE} ShapeType;

typedef struct shape *Shape;
typedef struct shape {

    ShapeType type;

    Texture texture;

    union {
        Sphere sphere;
        Plane plane;
        Triangle triangle;
    };

} ShapeData;

Shape shape_sphere(Vector3D position, double radius, Texture texture);

Shape shape_plane(Vector3D position, Vector3D normal, Texture texture);

Shape shape_triangle(
    Vector3D point1,
    Vector3D point2,
    Vector3D point3,
    Texture texture
);

double shape_intersect(Shape shape, Ray ray);

void shape_cleanup(Shape shape);

Vector3D shape_normal(Shape shape, Vector3D pos);

#endif

