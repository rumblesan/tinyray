#include <stdlib.h>
#include <math.h>

#include "core/lights.h"
#include "core/coordinates.h"

Light light_create(Coord3D centre, double intensity) {

    Light light = (Light) malloc(sizeof(Light_Data));

    light->centre = centre;

    light->intensity = intensity;

    return light;
}

void light_cleanup(Light light) {
    free(light);
}


