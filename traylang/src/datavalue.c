#include <stdlib.h>

#include "dbg.h"
#include "datavalue.h"

DataValue *datavalue_create(DataType type, void *value) {
    DataValue *data = malloc(sizeof(DataValue));
    check_mem(data);
    data->type = type;
    data->value = value;
    return data;
error:
    return NULL;
}

DataValue *datavalue_function(func_cb func) {
    return datavalue_create(FUNCTION, func);
}

DataValue *datavalue_list(List *list) {
    return datavalue_create(LIST, list);
}

DataValue *datavalue_nothing() {
    return datavalue_create(NOTHING, NULL);
}

DataValue *datavalue_number(double num) {
    double *val = malloc(sizeof(double));
    *val = num;
    return datavalue_create(NUMBER, val);
}

DataValue *datavalue_string(bstring string) {
    return datavalue_create(STRING, string);
}

DataValue *datavalue_cdata(void *cdata) {
    return datavalue_create(CDATA, cdata);
}

void datavalue_destroy(DataValue *data) {
    free(data);
}

void datavalue_clear_destroy(DataValue *data) {
    switch(data->type) {
        case FUNCTION:
            debug("Not freeing up function pointer");
            break;
        case LIST:
            list_clear_destroy(data->value);
            break;
        case NOTHING:
            debug("Not freeing up Nothing");
            break;
        case NUMBER:
            free(data->value);
            break;
        case STRING:
            bdestroy(data->value);
            break;
        case CDATA:
            debug("Not freeing up CData");
            break;
    }
    free(data);
}

func_cb datavalue_get_function(DataValue *data) {
    return data->value;
}

List *datavalue_get_list(DataValue *data){
    return data->value;
}

double datavalue_get_number(DataValue *data){
    double *v = data->value;
    return *v;
}

bstring datavalue_get_string(DataValue *data){
    return data->value;
}

void *datavalue_get_cdata(DataValue *data){
    return data->value;
}

