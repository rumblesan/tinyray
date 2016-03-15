#include <stdlib.h>

#include "language/interpreter.h"
#include "language/stdlib/list.h"
#include "bclib/list.h"

DataValue *list(List *args) {
    List *list = list_create();
    LIST_FOREACH(args, first, next, el) {
        list_unshift(list, el->value);
    }
    return datavalue_create(LIST, list);
}

DataValue *append(List *args) {
    DataValue *list = list_get(args, 0);
    DataValue *v = list_get(args, 1);
    list_unshift(list->value, v->value);
    return datavalue_create(LIST, list);
}

