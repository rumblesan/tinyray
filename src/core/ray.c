#include "core/ray.h"

#include "core/vector.h"

Ray ray(Vector3D origin, Vector3D direction) {
    Ray ray;

    ray.origin  = origin;
    ray.direction = direction;

    return ray;
}

