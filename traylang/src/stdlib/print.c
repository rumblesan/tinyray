#include <stdio.h>

#include "stdlib/print.h"

#include "interpreter.h"
#include "interpreter_funcs.h"
#include "object.h"
#include "bclib/list.h"

Object *print(Interpreter *interpreter, int arg_num) {
    int i;
    for (i = 0; i < arg_num; i += 1) {
        print_value(get_arg(interpreter));
    }
    return object_nothing(interpreter);
}

void print_value(Object *obj) {
    double *v;
    bstring str;
    switch(obj->type) {
        case FUNCTION:
            printf("Function\n");
            break;
        case LIST:
            print_list(obj->value);
            break;
        case NOTHING:
            printf("Nothing\n");
            break;
        case NUMBER:
            v = obj->value;
            printf("%f\n", *v);
            break;
        case STRING:
            str = obj->value;
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

