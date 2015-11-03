#include <stdlib.h>
#include <math.h>

#include "core/camera.h"
#include "core/vector.h"

Camera camera_create(Vector3D position, Vector3D looking_at) {

    Camera camera = (Camera) malloc(sizeof(CameraData));

    camera->position = position;
    camera->looking_at = looking_at;

    return camera;
}

void camera_cleanup(Camera camera) {
    free(camera);
}


