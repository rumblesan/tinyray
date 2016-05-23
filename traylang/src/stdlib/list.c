#include <stdlib.h>

#include "interpreter.h"
#include "interpreter_funcs.h"
#include "datavalue.h"
#include "stdlib/list.h"
#include "bclib/list.h"

DataValue *list(Interpreter *interpreter, int arg_num) {
    int i;
    List *list = list_create();
    for (i = 0; i < arg_num; i += 1) {
        list_push(list, get_arg(interpreter));
    }
    return datavalue_list(list);
}

DataValue *append(Interpreter *interpreter, int arg_num) {
    List *list = get_arg(interpreter);
    void *v = get_arg(interpreter);
    list_push(list, v);
    return datavalue_list(list);
}

