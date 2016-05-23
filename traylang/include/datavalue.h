#ifndef TRAYLANG_DATAVALUE_H
#define TRAYLANG_DATAVALUE_H

#include "bclib/list.h"
#include "bclib/bstrlib.h"

typedef enum {FUNCTION, LIST, NOTHING, NUMBER, STRING, CDATA} DataType;

typedef struct DataValue {

    DataType type;

    void *value;

} DataValue;

typedef DataValue *(*func_cb)(List *args);

DataValue *datavalue_function(func_cb func);

DataValue *datavalue_list(List *list);

DataValue *datavalue_nothing();

DataValue *datavalue_number(double number);

DataValue *datavalue_string(bstring string);

DataValue *datavalue_cdata(void *cdata);

void datavalue_destroy(DataValue *data);

void datavalue_clear_destroy(DataValue *data);

func_cb datavalue_get_function(DataValue *data);

List *datavalue_get_list(DataValue *data);

void *datavalue_get_nothing(DataValue *data);

double datavalue_get_number(DataValue *data);

bstring datavalue_get_string(DataValue *data);

void *datavalue_get_cdata(DataValue *data);

#endif
