#include <stdio.h>

#include "interpreter.h"
#include "stdlib/print.h"
#include "bclib/list.h"

DataValue *print(List *args) {
    DataValue *arg1 = list_get(args, 0);
    print_value(arg1);
    return datavalue_nothing();
}

void print_value(DataValue *data) {
    double *v;
    switch(data->type) {
        case FUNCTION:
            printf("Function\n");
            break;
        case LIST:
            print_list(data->value);
            break;
        case NOTHING:
            printf("Nothing\n");
            break;
        case NUMBER:
            v = data->value;
            printf("%f\n", *v);
            break;
        case CDATA:
            printf("C Data\n");
            break;
        default:
            printf("Something else\n");
            break;
    }
}

void print_list(List *list) {
    printf("List\n");
    LIST_FOREACH(list, first, next, el) {
        print_value(el->value);
    }
}

