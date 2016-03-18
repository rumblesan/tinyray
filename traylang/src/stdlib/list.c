#include <stdlib.h>

#include "datavalue.h"
#include "stdlib/list.h"
#include "bclib/list.h"

DataValue *list(List *args) {
    List *list = list_create();
    LIST_FOREACH(args, first, next, el) {
        list_push(list, el->value);
    }
    return datavalue_list(list);
}

DataValue *append(List *args) {
    DataValue *list = list_get(args, 0);
    DataValue *v = list_get(args, 1);
    list_push(list->value, v->value);
    return list;
}

