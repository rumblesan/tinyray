#ifndef LIGHTS_H
#define LIGHTS_H

#include "vector.h"
#include "colours.h"

typedef enum {POINT, AMBIENT} LightType;

typedef struct PointLight {

    Vector3D position;

} PointLight;

typedef struct Light {

    LightType type;

    Colour colour;

    double intensity;

    union {
        PointLight point;
    };

} Light;

Light *point_light_create(Vector3D position, double intensity, Colour colour);

Light *ambient_light_create(double intensity, Colour colour);

void light_destroy(Light *light);

#endif

