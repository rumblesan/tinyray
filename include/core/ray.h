#ifndef RAY_H
#define RAY_H

#include "core/vector.h"

typedef struct ray {

    Vector3D point;

    Vector3D vector;

} Ray;

Ray ray(Vector3D point, Vector3D vector);

#endif
