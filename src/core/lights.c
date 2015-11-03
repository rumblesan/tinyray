#include <stdlib.h>
#include <math.h>

#include "core/lights.h"
#include "core/vector.h"

Light light_create(double x, double y, double z, double intensity) {

    Light light = (Light) malloc(sizeof(LightData));

    light->centre = vector3d_create(x, y, z);

    light->intensity = intensity;

    return light;
}

void light_cleanup(Light light) {
    vector3d_cleanup(light->centre);
    free(light);
}


