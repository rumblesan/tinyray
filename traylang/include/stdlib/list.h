#ifndef LANGUAGE_STDLIB_LIST_H
#define LANGUAGE_STDLIB_LIST_H

#include "interpreter.h"
#include "bclib/list.h"

DataValue *list(List *args);

DataValue *append(List *args);

#endif
