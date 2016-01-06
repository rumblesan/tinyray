#ifndef CANVAS_H
#define CANVAS_H

#include "colours.h"

typedef struct canvas *Canvas;
typedef struct canvas {

    int width;
    int height;

    Colour **data;

} CanvasData;

Canvas canvas_create(int width, int height);

void canvas_set(Canvas canvas, int x, int y, Colour colour);

Colour canvas_get(Canvas canvas, int x, int y);

void canvas_cleanup(Canvas canvas);

#endif

