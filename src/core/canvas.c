#include <stdlib.h>

#include "core/canvas.h"

#include "core/colours.h"

Canvas canvas_create(int width, int height) {

    Canvas canvas = (Canvas) malloc(sizeof(CanvasData));

    canvas->width = width;
    canvas->height = height;

    canvas->data = malloc(width * sizeof(Colour*));
    int i;
    for (i = 0; i < width; i += 1) {
        canvas->data[i] = malloc(height * sizeof(Colour));
    }

    return canvas;
}

void canvas_set(Canvas canvas, int x, int y, Colour colour) {
    canvas->data[x][y] = colour;
}

Colour canvas_get(Canvas canvas, int x, int y) {
    return canvas->data[x][y];
}

void canvas_cleanup(Canvas canvas) {
    int i;
    for (i = 0; i < canvas->width; i += 1) {
        free(canvas->data[i]);
    }
    free(canvas->data);

    free(canvas);
}

