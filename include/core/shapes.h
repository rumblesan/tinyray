#ifndef SHAPES_H
#define SHAPES_H

#include "core/vector.h"
#include "core/ray.h"
#include "core/textures.h"

typedef enum {SPHERE, PLANE} ShapeType;

typedef struct plane *Plane;
typedef struct plane {

    Vector3D position;

    Vector3D normal;

} PlaneData;

typedef struct sphere *Sphere;
typedef struct sphere {

    Vector3D centre;

    double radius;

} SphereData;

typedef struct shape *Shape;
typedef struct shape {

    ShapeType type;

    Texture texture;

    union {
        Sphere sphere;
        Plane plane;
    };

} ShapeData;

double shape_intersect(Shape shape, Ray ray);

void shape_cleanup(Shape shape);

Vector3D shape_normal(Shape shape, Vector3D pos);

/* Sphere functions */
Shape sphere_create(Vector3D position, double radius, Texture texture);

double sphere_intersect(Sphere sphere, Ray ray);

Vector3D sphere_normal(Sphere sphere, Vector3D pos);

void sphere_cleanup(Sphere shape);

/* Plane functions */
Shape plane_create(Vector3D position, Vector3D normal, Texture texture);

double plane_intersect(Plane plane, Ray ray);

Vector3D plane_normal(Plane plane, Vector3D pos);

void plane_cleanup(Plane plane);

#endif

