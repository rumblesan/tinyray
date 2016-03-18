#include "minunit.h"

#include "datavalue.h"

static DataValue *data = NULL;

static char * test_create() {
    DataValue *data = datavalue_create(NOTHING, NULL);
    mu_assert(interpreter != NULL, "failed to create datavalue");
    return 0;
}

static char *test_destroy() {
    datavalue_destroy(data);
    return 0;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
