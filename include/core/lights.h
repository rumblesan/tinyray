#ifndef LIGHTS_H
#define LIGHTS_H

#include "core/vector.h"

typedef struct light_point {

    Vector3D centre;

    double intensity;

} Light;

Light light_create(Vector3D position, double intensity);

#endif

