#include "stdlib/list.h"

#include "interpreter.h"
#include "interpreter_funcs.h"
#include "object.h"
#include "bclib/list.h"

Object *list(Interpreter *interpreter, int arg_num) {
    int i;
    List *list = list_create();
    for (i = 0; i < arg_num; i += 1) {
        list_push(list, get_obj(interpreter));
    }
    return object_list(interpreter, list);
}

Object *append(Interpreter *interpreter, int arg_num) {
    Object *list_obj = get_obj(interpreter);
    Object *arg_obj = get_obj(interpreter);
    list_push(list_obj->list, arg_obj);
    return list_obj;
}

