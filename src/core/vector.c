#include <stdlib.h>
#include <math.h>

#include "core/vector.h"

Vector3D vector3d_create(double x, double y, double z) {

    Vector3D vector = (Vector3D) malloc(sizeof(Vector3DData));

    vector->x = x;
    vector->y = y;
    vector->z = z;

    return vector;
}

void vector3d_cleanup(Vector3D vector) {
    free(vector);
}

