#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector_3d *Vector3D;
typedef struct vector_3d {

    double x;
    double y;
    double z;

} Vector3DData;

Vector3D vector3d_create(double x, double y, double z);

Vector3D vector3d_add(Vector3D vectA, Vector3D vectB);

Vector3D vector3d_subtract(Vector3D vectA, Vector3D vectB);

Vector3D vector3d_scale(double scalar, Vector3D vect);

double vector3d_length(Vector3D vect);

Vector3D vector3d_unit(Vector3D vect);

void vector3d_cleanup(Vector3D coord);

#endif
