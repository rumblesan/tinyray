#include <stdlib.h>
#include <math.h>

#include "core/coordinates.h"

Coord3D coord3d_create(double x, double y, double z) {

    Coord3D coord = (Coord3D) malloc(sizeof(Coord3D_Data));

    coord->x = x;
    coord->y = y;
    coord->z = z;

    return coord;
}

void coord3d_cleanup(Coord3D coord) {
    free(coord);
}

