#include "minunit.h"

#include "colours.h"

static char * test_normalise() {

    Colour c1 = colour(255, 0, 100);

    Colour out = colour_normalise(
        colour_scale(c1, 3)
    );

    mu_assert(out.red == 255, "Error: Red Colour normalisation must work correctly");
    mu_assert(out.green == 0, "Error: Green Colour normalisation must work correctly");
    mu_assert(out.blue == 100, "Error: Blue Colour normalisation must work correctly");

    return 0;
}

static char * test_ceil() {

    Colour c1 = colour(200, 50, 200);

    Colour out = colour_ceil(
        colour_scale(c1, 3)
    );

    mu_assert(out.red == 255, "Error: Red Colour ceil must work correctly");
    mu_assert(out.green == 150, "Error: Green Colour ceil must work correctly");
    mu_assert(out.blue == 255, "Error: Blue Colour ceil must work correctly");

    return 0;
}

/*
 *static char * test_brightness() {
 *
 *    Colour c1 = colour(255, 255, 255);
 *
 *    double brightness = colour_brightness(c1);
 *
 *    mu_assert("Error: Colour brightness must work correctly", brightness == (double)1);
 *
 *    return 0;
 *}
 */

static char * test_filter() {

    Colour c1 = colour(255, 100, 200);
    Colour filter = colour(255, 127.5, 63.75);

    Colour filtered = colour_filter(c1, filter);

    mu_assert(filtered.red == 255, "Error: Filtered red must work correctly");
    mu_assert(filtered.green == 50, "Error: Filtered green must work correctly");
    mu_assert(filtered.blue == 50, "Error: Filtered blue must work correctly");

    return 0;
}

char * test_colours() {
    return 0;
}


char *all_tests() {
    mu_suite_start();

    mu_run_test(test_normalise);
    mu_run_test(test_ceil);
    mu_run_test(test_filter);

    return NULL;
}

RUN_TESTS(all_tests);
