#include "core/lights.h"

#include "core/vector.h"

Light light_create(double x, double y, double z, double intensity) {

    Light light;

    light.centre = vector3d(x, y, z);

    light.intensity = intensity;

    return light;
}

