#include <stdlib.h>

#include "camera.h"

#include "vector.h"

Camera *camera_create(double fov, Vector3D position, Vector3D looking_at) {

    Camera *camera = malloc(sizeof(Camera));

    camera->fov = fov;
    camera->position = position;
    camera->looking_at = looking_at;

    return camera;
}

void camera_cleanup(Camera *camera) {
    free(camera);
}


