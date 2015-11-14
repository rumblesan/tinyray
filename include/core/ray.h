#ifndef RAY_H
#define RAY_H

#include "core/vector.h"

typedef struct ray {

    Vector3D origin;

    Vector3D direction;

} Ray;

Ray ray(Vector3D origin, Vector3D direction);

Ray ray_from_to(Vector3D origin, Vector3D target);

#endif
