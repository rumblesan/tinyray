#ifndef SHAPES_H
#define SHAPES_H

#include "core/vector.h"
#include "core/ray.h"
#include "core/textures.h"

#include "core/shapes/sphere.h"
#include "core/shapes/plane.h"

typedef enum {SPHERE, PLANE} ShapeType;

typedef struct shape *Shape;
typedef struct shape {

    ShapeType type;

    Texture texture;

    union {
        Sphere sphere;
        Plane plane;
    };

} ShapeData;

Shape shape_sphere(Vector3D position, double radius, Texture texture);

Shape shape_plane(Vector3D position, Vector3D normal, Texture texture);

double shape_intersect(Shape shape, Ray ray);

void shape_cleanup(Shape shape);

Vector3D shape_normal(Shape shape, Vector3D pos);

#endif

