#ifndef TRAYLANG_DATAVALUE_H
#define TRAYLANG_DATAVALUE_H

#include "interpreter.h"
#include "bclib/list.h"
#include "bclib/bstrlib.h"

typedef enum {FUNCTION, LIST, NOTHING, NUMBER, STRING, CDATA} DataType;

typedef struct DataValue {

    DataType type;

    void *value;

} DataValue;

typedef DataValue *(*func_cb)(Interpreter *interpreter, int arg_count);

DataValue *datavalue_function(func_cb func);

DataValue *datavalue_list(List *list);

DataValue *datavalue_nothing();

DataValue *datavalue_number(double number);

DataValue *datavalue_string(bstring string);

DataValue *datavalue_cdata(void *cdata);

void datavalue_destroy(DataValue *data);

void datavalue_clear_destroy(DataValue *data);

#endif
