#ifndef CAMERA_H
#define CAMERA_H

#include "core/vector.h"

typedef struct camera *Camera;
typedef struct camera {

    double fov;

    Vector3D position;

    Vector3D looking_at;

} CameraData;

Camera camera_create(double fov, Vector3D position, Vector3D looking_at);

void camera_cleanup(Camera camera);

#endif

