#ifndef CAMERA_H
#define CAMERA_H

#include "core/coordinates.h"

typedef struct camera *Camera;
typedef struct camera {

    Coord3D position;

    Coord3D looking_at;

} Camera_Data;

Camera camera_create(Coord3D position, Coord3D looking_at);

void camera_cleanup(Camera camera);

#endif

