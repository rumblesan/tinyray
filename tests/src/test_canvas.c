#include "tests/min_unit.h"

#include "core/canvas.h"
#include "core/colours.h"

static char * test_creation() {

    Canvas canvas = canvas_create(640, 480);

    mu_assert("Error: Canvas object not created correctly", canvas->width == 640);

    canvas_cleanup(canvas);
    return 0;
}

static char * test_get_set() {

    Canvas canvas = canvas_create(640, 480);
    Colour c = colour(0, 0, 100);
    canvas_set(canvas, 4, 5, c);

    Colour retc = canvas_get(canvas, 4, 5);
    mu_assert("Error: Canvas get/set doesn't work", retc.red == c.red);

    return 0;
}

char * test_canvas() {
    mu_run_test(test_creation);
    mu_run_test(test_get_set);
    return 0;
}

