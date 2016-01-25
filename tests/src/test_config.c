#include "minunit.h"

#include "config.h"
#include "colours.h"

static char * test_creation() {

    Colour background = colour(0, 100, 100);

    Config *config = config_create(640, 480, 1000, 7, background);

    mu_assert(config->width == 640, "Error: Config object not created correctly");

    config_cleanup(config);
    return 0;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_creation);

    return NULL;
}

RUN_TESTS(all_tests);
