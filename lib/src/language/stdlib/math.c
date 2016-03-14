#include <stdlib.h>

#include "language/interpreter.h"
#include "language/stdlib/misc.h"
#include "bclib/list.h"

DataValue *add(List *args) {
    DataValue *arg1 = list_shift(args);
    DataValue *arg2 = list_shift(args);
    double *v1 = arg1->value;
    double *v2 = arg2->value;
    double result = *v1 + *v2;
    double *val = malloc(sizeof(double));
    *val = result;
    return datavalue_create(NUMBER, val);
}

DataValue *sub(List *args) {
    DataValue *arg1 = list_shift(args);
    DataValue *arg2 = list_shift(args);
    double *v1 = arg1->value;
    double *v2 = arg2->value;
    double result = *v1 - *v2;
    double *val = malloc(sizeof(double));
    *val = result;
    return datavalue_create(NUMBER, val);
}

