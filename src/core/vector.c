#include <stdlib.h>
#include <math.h>

#include "core/vector.h"

Vector3D vector3d(double x, double y, double z) {

    Vector3D vector;

    vector.x = x;
    vector.y = y;
    vector.z = z;

    return vector;
}

Vector3D vector3d_add(Vector3D vectA, Vector3D vectB) {

    Vector3D newV;

    newV.x = (vectA.x + vectB.x);
    newV.y = (vectA.y + vectB.y);
    newV.z = (vectA.z + vectB.z);

    return newV;
}

Vector3D vector3d_subtract(Vector3D vectA, Vector3D vectB) {

    Vector3D newV;

    newV.x = (vectA.x - vectB.x);
    newV.y = (vectA.y - vectB.y);
    newV.z = (vectA.z - vectB.z);

    return newV;
}

Vector3D vector3d_scale(double scalar, Vector3D vect) {

    Vector3D newV;

    newV.x = (vect.x * scalar);
    newV.y = (vect.y * scalar);
    newV.z = (vect.z * scalar);

    return newV;
}

double vector3d_length(Vector3D vect) {
    return sqrt(
        pow(vect.x, 2) + pow(vect.y, 2) + pow(vect.z, 2)
    );
}

Vector3D vector3d_unit(Vector3D vect) {

    double length = vector3d_length(vect);

    Vector3D newV;

    newV.x = (vect.x / length);
    newV.y = (vect.y / length);
    newV.z = (vect.z / length);

    return newV;
}

Vector3D vector3d_cross(Vector3D vectA, Vector3D vectB) {

    Vector3D newV;

    newV.x = (vectA.y * vectB.z) - (vectA.z * vectB.y);
    newV.y = (vectA.z * vectB.x) - (vectA.x * vectB.z);
    newV.z = (vectA.x * vectB.y) - (vectA.y * vectB.x);

    return newV;
}

double vector3d_dot(Vector3D vectA, Vector3D vectB) {
    return ((vectA.x * vectB.x) + (vectA.y + vectB.y) + (vectA.z + vectB.z));
}

