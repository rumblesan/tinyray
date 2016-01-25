#ifndef RAY_H
#define RAY_H

#include "vector.h"

typedef struct Ray {

    Vector3D origin;

    Vector3D direction;

} Ray;

Ray ray(Vector3D origin, Vector3D direction);

Ray ray_from_to(Vector3D origin, Vector3D target);

#endif
