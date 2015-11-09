#include "core/lights.h"

#include "core/vector.h"
#include "core/colours.h"

Light ambient_light_create(double intensity, Colour colour) {
    AmbientLight ambient;

    Light light;
    light.ambient = ambient;
    light.type = AMBIENT;
    light.colour = colour;
    light.intensity = intensity;
    return light;
}

Light point_light_create(Vector3D position, double intensity, Colour colour) {
    PointLight point;
    point.position = position;

    Light light;
    light.point = point;
    light.type = POINT;
    light.colour = colour;
    light.intensity = intensity;
    return light;
}

