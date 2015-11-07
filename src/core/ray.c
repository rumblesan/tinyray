#include "core/ray.h"

#include "core/vector.h"

Ray ray(Vector3D point, Vector3D vector) {
    Ray ray;

    ray.point  = point;
    ray.vector = vector;

    return ray;
}

