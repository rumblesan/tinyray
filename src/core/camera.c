#include <stdlib.h>

#include "core/camera.h"

#include "core/vector.h"

Camera camera_create(
    double fov,
    double posx, double posy, double posz,
    double lookx, double looky, double lookz
) {

    Camera camera = (Camera) malloc(sizeof(CameraData));

    camera->fov = fov;
    camera->position = vector3d(posx, posy, posz);
    camera->looking_at = vector3d(lookx, looky, lookz);

    return camera;
}

void camera_cleanup(Camera camera) {
    free(camera);
}


