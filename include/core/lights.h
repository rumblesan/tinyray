#ifndef LIGHTS_H
#define LIGHTS_H

#include "core/vector.h"

typedef struct light_point {

    Vector3D centre;

    double intensity;

} Light;

Light light_create(double x, double y, double z, double intensity);

#endif

