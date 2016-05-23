#include "minunit.h"

#include "datavalue.h"

static char * test_number() {
    DataValue *data = datavalue_number(3);
    mu_assert(data != NULL, "failed to create datavalue");
    double *num = data->value;
    mu_assert(*num == 3, "incorrect number in datavalue");
    datavalue_clear_destroy(data);
    return 0;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_number);

    return NULL;
}

RUN_TESTS(all_tests);
