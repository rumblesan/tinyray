#include "tests/min_unit.h"

#include "core/config.h"
#include "core/colours.h"

static char * test_creation() {

    Colour background = colour(0, 100, 100);

    Config config = config_create(640, 480, 1000, background);

    mu_assert("Error: Config object not created correctly", config->width == 640);

    config_cleanup(config);
    return 0;
}

char * test_config() {
    mu_run_test(test_creation);
    return 0;
}

