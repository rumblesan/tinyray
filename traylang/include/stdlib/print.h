#ifndef LANGUAGE_STDLIB_MISC_H
#define LANGUAGE_STDLIB_MISC_H

#include "interpreter.h"
#include "object.h"
#include "bclib/list.h"

Object *print(Interpreter *interpreter, int arg_num);

void print_value(Object *obj);

void print_list(List *list);

#endif
