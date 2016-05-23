#include "minunit.h"

#include "object.h"

static char * test_number() {
    Object *obj = object_number(3);
    mu_assert(obj != NULL, "failed to create object");
    double *num = obj->value;
    mu_assert(*num == 3, "incorrect number in object");
    object_clear_destroy(obj);
    return 0;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_number);

    return NULL;
}

RUN_TESTS(all_tests);
