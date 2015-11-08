#include "core/lights.h"

#include "core/vector.h"

Light light_create(Vector3D position, double intensity) {

    Light light;

    light.position = position;

    light.intensity = intensity;

    return light;
}

