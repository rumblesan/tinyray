#ifndef COORDINATES_H
#define COORDINATES_H

typedef struct coord_3d *Coord3D;
typedef struct coord_3d {

    double x;
    double y;
    double z;

} Coord3D_Data;

Coord3D coord3d_create(double x, double y, double z);

void coord3d_cleanup(Coord3D coord);

#endif
