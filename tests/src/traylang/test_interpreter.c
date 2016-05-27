#include "minunit.h"

#include "interpreter.h"
#include "interpreter_funcs.h"

static Interpreter *interpreter = NULL;


static char * test_create() {
    interpreter = interpreter_create();
    mu_assert(interpreter != NULL, "failed to create interpreter");
    return 0;
}

static char *test_destroy() {
    interpreter_destroy(interpreter);
    return 0;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
