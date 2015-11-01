#include "tests/min_unit.h"

#include "core/config.h"

static char * test_creation() {

    Config config = config_create(640, 480, 0);

    mu_assert("Error: Config object not created correctly", config->width == 640);

    config_cleanup(config);
    return 0;
}

char * test_config() {
    mu_run_test(test_creation);
    return 0;
}

