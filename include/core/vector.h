#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector_3d {

    double x;
    double y;
    double z;

} Vector3D;

Vector3D vector3d(double x, double y, double z);

Vector3D vector3d_add(Vector3D vectA, Vector3D vectB);

Vector3D vector3d_subtract(Vector3D vectA, Vector3D vectB);

Vector3D vector3d_scale(double scalar, Vector3D vect);

double vector3d_length(Vector3D vect);

Vector3D vector3d_unit(Vector3D vect);

Vector3D vector3d_cross(Vector3D vectA, Vector3D vectB);

double vector3d_dot(Vector3D vectA, Vector3D vectB);

Vector3D vector3d_reflection(Vector3D normal, Vector3D direction);

#endif
