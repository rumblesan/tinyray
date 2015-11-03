#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector_3d *Vector3D;
typedef struct vector_3d {

    double x;
    double y;
    double z;

} Vector3DData;

Vector3D vector3d_create(double x, double y, double z);

void vector3d_cleanup(Vector3D coord);

#endif
