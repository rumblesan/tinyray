#ifndef LANGUAGE_STDLIB_LIST_H
#define LANGUAGE_STDLIB_LIST_H

#include "interpreter.h"
#include "datavalue.h"
#include "bclib/list.h"

DataValue *list(Interpreter *interpreter, int arg_num);

DataValue *append(Interpreter *interpreter, int arg_num);

#endif

