#include <stdlib.h>

#include "dbg.h"
#include "datavalue.h"

DataValue *datavalue_create(DataType type, void *value) {
    DataValue *data_value = malloc(sizeof(DataValue));
    check_mem(data_value);
    data_value->type = type;
    data_value->value = value;
    data_value->ref_count = 1;
    return data_value;
error:
    return NULL;
}

void datavalue_destroy(DataValue *data) {
    if (data->value) free(data->value);
    free(data);
}

DataValue *datavalue_incr_ref(DataValue *value) {
    check(value, "DataValue is null");
    value->ref_count += 1;
    return value;
error:
    return NULL;
}

void *datavalue_decr_ref(DataValue *value) {
    check(value, "DataValue is null");
    check(value->ref_count >= 1, "DataValue ref count can't be less than 0");
    value->ref_count -= 1;
    if (value->ref_count == 0) {
        free(value);
    }
    return NULL;
error:
    if (value) {
        free(value);
    }
    return NULL;
}

