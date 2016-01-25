#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"

typedef struct Camera {

    double fov;

    Vector3D position;

    Vector3D looking_at;

} Camera;

Camera *camera_create(double fov, Vector3D position, Vector3D looking_at);

void camera_cleanup(Camera *camera);

#endif

