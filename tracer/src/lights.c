#include <stdlib.h>

#include "lights.h"

#include "vector.h"
#include "colours.h"

Light *ambient_light_create(double intensity, Colour colour) {

    Light *light = malloc(sizeof(Light));

    AmbientLight ambient;

    light->ambient = ambient;
    light->type = AMBIENT;
    light->colour = colour;
    light->intensity = intensity;

    return light;
}

Light *point_light_create(Vector3D position, double intensity, Colour colour) {
    Light *light = malloc(sizeof(Light));

    PointLight point;
    point.position = position;

    light->point = point;
    light->type = POINT;
    light->colour = colour;
    light->intensity = intensity;

    return light;
}

void light_destroy(Light *light) {
    free(light);
}

