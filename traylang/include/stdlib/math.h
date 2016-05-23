#ifndef LANGUAGE_STDLIB_MATH_H
#define LANGUAGE_STDLIB_MATH_H

#include "interpreter.h"
#include "object.h"

Object *add(Interpreter *interpreter, int arg_num);

Object *sub(Interpreter *interpreter, int arg_num);

#endif

