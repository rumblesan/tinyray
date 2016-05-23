#ifndef LANGUAGE_STDLIB_MISC_H
#define LANGUAGE_STDLIB_MISC_H

#include "interpreter.h"
#include "datavalue.h"
#include "bclib/list.h"

DataValue *print(Interpreter *interpreter, int arg_num);

void print_value(DataValue *data);

void print_list(List *list);

#endif
