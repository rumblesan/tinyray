#ifndef TRAYLANG_DATAVALUE_H
#define TRAYLANG_DATAVALUE_H

#include "bclib/list.h"

typedef enum {FUNCTION, LIST, NOTHING, NUMBER, CDATA} DataType;

typedef struct DataValue {

    DataType type;

    void *value;

    int ref_count;

} DataValue;

typedef DataValue *(*func_cb)(List *args);

DataValue *datavalue_function(func_cb func);

DataValue *datavalue_list(List *list);

DataValue *datavalue_nothing();

DataValue *datavalue_number(double number);

DataValue *datavalue_cdata(void *cdata);

void datavalue_destroy(DataValue *data);

func_cb datavalue_get_function(DataValue *data);

List *datavalue_get_list(DataValue *data);

void *datavalue_get_nothing(DataValue *data);

double datavalue_get_number(DataValue *data);

void *datavalue_get_cdata(DataValue *data);

DataValue *datavalue_incr_ref(DataValue *data);

void *datavalue_decr_ref(DataValue *data);

#endif
