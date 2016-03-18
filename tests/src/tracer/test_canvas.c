#include "minunit.h"

#include "canvas.h"
#include "colours.h"

static char * test_creation() {

    Canvas *canvas = canvas_create(640, 480);

    mu_assert(canvas->width == 640 ,"Error: Canvas object not created correctly");

    canvas_cleanup(canvas);
    return 0;
}

static char * test_get_set() {

    Canvas *canvas = canvas_create(640, 480);
    Colour c = colour(0, 0, 100);
    canvas_set(canvas, 4, 5, c);

    Colour retc = canvas_get(canvas, 4, 5);
    mu_assert(retc.red == c.red ,"Error: Canvas get/set doesn't work");

    return 0;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_creation);
    mu_run_test(test_get_set);
    return NULL;
}

RUN_TESTS(all_tests);
