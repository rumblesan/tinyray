#include <stdlib.h>

#include "dbg.h"
#include "datavalue.h"

DataValue *datavalue_create(DataType type, void *value) {
    DataValue *data_value = malloc(sizeof(DataValue));
    check_mem(data_value);
    data_value->type = type;
    data_value->value = value;
    return data_value;
error:
    return NULL;
}

