#include "min_unit.h"

#include "colours.h"

static char * test_normalise() {

    Colour c1 = colour(255, 0, 100);

    Colour out = colour_normalise(
        colour_scale(c1, 3)
    );

    mu_assert("Error: Red Colour normalisation must work correctly", out.red == 255);
    mu_assert("Error: Green Colour normalisation must work correctly", out.green == 0);
    mu_assert("Error: Blue Colour normalisation must work correctly", out.blue == 100);

    return 0;
}

static char * test_ceil() {

    Colour c1 = colour(200, 50, 200);

    Colour out = colour_ceil(
        colour_scale(c1, 3)
    );

    mu_assert("Error: Red Colour ceil must work correctly", out.red == 255);
    mu_assert("Error: Green Colour ceil must work correctly", out.green == 150);
    mu_assert("Error: Blue Colour ceil must work correctly", out.blue == 255);

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

    mu_assert("Error: Filtered red must work correctly", filtered.red == 255);
    mu_assert("Error: Filtered green must work correctly", filtered.green == 50);
    mu_assert("Error: Filtered blue must work correctly", filtered.blue == 50);

    return 0;
}

char * test_colours() {
    mu_run_test(test_normalise);
    mu_run_test(test_ceil);
    mu_run_test(test_filter);
    return 0;
}


