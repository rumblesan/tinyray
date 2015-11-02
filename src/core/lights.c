#include <stdlib.h>
#include <math.h>

#include "core/lights.h"
#include "core/coordinates.h"

Light light_create(double x, double y, double z, double intensity) {

    Light light = (Light) malloc(sizeof(LightData));

    light->centre = coord3d_create(x, y, z);

    light->intensity = intensity;

    return light;
}

void light_cleanup(Light light) {
    coord3d_cleanup(light->centre);
    free(light);
}


