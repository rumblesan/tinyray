#ifndef CANVAS_H
#define CANVAS_H

#include "colours.h"

typedef struct Canvas {

    int width;
    int height;

    Colour **data;

} Canvas;

Canvas *canvas_create(int width, int height);

void canvas_set(Canvas *canvas, int x, int y, Colour colour);

Colour canvas_get(Canvas *canvas, int x, int y);

void canvas_cleanup(Canvas *canvas);

#endif

