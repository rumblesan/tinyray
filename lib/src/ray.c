#include "ray.h"

#include "vector.h"

Ray ray(Vector3D origin, Vector3D direction) {
    Ray ray;

    ray.origin  = origin;
    ray.direction = direction;

    return ray;
}

Ray ray_from_to(Vector3D origin, Vector3D target) {
    Vector3D direction = vector3d_unit(
        vector3d_subtract(target, origin)
    );
    return ray(origin, direction);
}

