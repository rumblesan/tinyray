#ifndef LANGUAGE_STDLIB_LIST_H
#define LANGUAGE_STDLIB_LIST_H

#include "interpreter.h"
#include "object.h"

Object *list(Interpreter *interpreter, int arg_num);

Object *append(Interpreter *interpreter, int arg_num);

#endif

