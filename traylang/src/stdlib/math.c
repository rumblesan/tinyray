#include "stdlib/math.h"

#include "interpreter.h"
#include "interpreter_funcs.h"
#include "object.h"

Object *add(Interpreter *interpreter, int arg_num) {
    Object *v1 = get_obj(interpreter);
    Object *v2 = get_obj(interpreter);
    double result = v1->number + v2->number;
    return object_number(interpreter, result);
}

Object *sub(Interpreter *interpreter, int arg_num) {
    Object *v1 = get_obj(interpreter);
    Object *v2 = get_obj(interpreter);
    double result = v1->number - v2->number;
    return object_number(interpreter, result);
}

