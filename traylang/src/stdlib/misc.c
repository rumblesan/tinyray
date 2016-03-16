#include <stdio.h>

#include "interpreter.h"
#include "stdlib/misc.h"
#include "bclib/list.h"

DataValue *print(List *args) {
    debug("Printing DataValue");
    DataValue *arg1 = list_get(args, 0);
    double *v;
    switch(arg1->type) {
        case NUMBER:
            v = arg1->value;
            printf("%f\n", *v);
            break;
        default:
            printf("Something else\n");
            break;
    }
    return datavalue_create(NOTHING, NULL);
}

