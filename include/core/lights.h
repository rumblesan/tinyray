#ifndef LIGHTS_H
#define LIGHTS_H

#include "core/coordinates.h"

typedef struct light_point *Light;
typedef struct light_point {

    Coord3D centre;

    double intensity;

} Light_Data;

Light light_create(Coord3D centre, double intensity);

void light_cleanup(Light light);

#endif

