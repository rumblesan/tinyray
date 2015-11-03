#ifndef LIGHTS_H
#define LIGHTS_H

#include "core/vector.h"

typedef struct light_point *Light;
typedef struct light_point {

    Vector3D centre;

    double intensity;

} LightData;

Light light_create(double x, double y, double z, double intensity);

void light_cleanup(Light light);

#endif

