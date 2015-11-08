#ifndef RAY_H
#define RAY_H

#include "core/vector.h"

typedef struct ray {

    Vector3D origin;

    Vector3D direction;

} Ray;

Ray ray(Vector3D origin, Vector3D direction);

#endif
