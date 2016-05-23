#ifndef LANGUAGE_STDLIB_MISC_H
#define LANGUAGE_STDLIB_MISC_H

#include "datavalue.h"
#include "bclib/list.h"

DataValue *print(List *args);

void print_value(DataValue *data);

void print_list(List *list);

#endif
