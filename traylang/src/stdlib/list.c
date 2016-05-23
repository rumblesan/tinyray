#include "stdlib/list.h"

#include "interpreter.h"
#include "interpreter_funcs.h"
#include "object.h"
#include "bclib/list.h"

Object *list(Interpreter *interpreter, int arg_num) {
    int i;
    List *list = list_create();
    for (i = 0; i < arg_num; i += 1) {
        list_push(list, get_arg(interpreter));
    }
    return object_list(list);
}

Object *append(Interpreter *interpreter, int arg_num) {
    List *list = get_arg(interpreter);
    void *v = get_arg(interpreter);
    list_push(list, v);
    return object_list(list);
}

