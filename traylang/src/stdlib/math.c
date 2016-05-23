#include "stdlib/math.h"

#include "interpreter.h"
#include "interpreter_funcs.h"
#include "datavalue.h"

DataValue *add(Interpreter *interpreter, int arg_num) {
    double *v1 = get_arg(interpreter);
    double *v2 = get_arg(interpreter);
    double result = *v1 + *v2;
    return datavalue_number(result);
}

DataValue *sub(Interpreter *interpreter, int arg_num) {
    double *v1 = get_arg(interpreter);
    double *v2 = get_arg(interpreter);
    double result = *v1 - *v2;
    return datavalue_number(result);
}

