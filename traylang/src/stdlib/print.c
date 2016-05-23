#include <stdio.h>

#include "stdlib/print.h"

#include "interpreter.h"
#include "interpreter_funcs.h"
#include "datavalue.h"
#include "bclib/list.h"

DataValue *print(Interpreter *interpreter, int arg_num) {
    DataValue *arg1 = interpreter_stack_pop(interpreter);
    print_value(arg1);
    return datavalue_nothing();
}

void print_value(DataValue *data) {
    double *v;
    bstring str;
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
        case STRING:
            str = data->value;
            printf("%s\n", str->data);
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

