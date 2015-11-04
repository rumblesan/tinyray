#ifndef CAMERA_H
#define CAMERA_H

#include "core/vector.h"

typedef struct camera *Camera;
typedef struct camera {

    Vector3D position;

    Vector3D looking_at;

} CameraData;

Camera camera_create(
    double posx, double posy, double posz,
    double lookx, double looky, double lookz
);

void camera_cleanup(Camera camera);

#endif

