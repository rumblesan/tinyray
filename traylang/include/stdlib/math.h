#ifndef LANGUAGE_STDLIB_MATH_H
#define LANGUAGE_STDLIB_MATH_H

#include "interpreter.h"
#include "datavalue.h"

DataValue *add(Interpreter *interpreter, int arg_num);

DataValue *sub(Interpreter *interpreter, int arg_num);

#endif

