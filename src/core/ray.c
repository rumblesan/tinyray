
#include "core/vector.h"
#include "core/ray.h"

Ray ray(Vector3D point, Vector3D vector) {
    Ray ray;

    ray.point  = point;
    ray.vector = vector;

    return ray;
}

