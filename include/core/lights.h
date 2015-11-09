#ifndef LIGHTS_H
#define LIGHTS_H

#include "core/vector.h"
#include "core/colours.h"

typedef enum {POINT, AMBIENT} LightType;

typedef struct point_light {

    Vector3D position;

} PointLight;

typedef struct ambient_light {

} AmbientLight;

typedef struct light {

    LightType type;

    Colour colour;

    double intensity;

    union {
        PointLight point;
        AmbientLight ambient;
    };

} Light;

Light point_light_create(Vector3D position, double intensity, Colour colour);

Light ambient_light_create(double intensity, Colour colour);

#endif

