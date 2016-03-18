#ifndef TRAYLANG_DATAVALUE_H
#define TRAYLANG_DATAVALUE_H

typedef enum {FUNCTION, LIST, NOTHING, NUMBER, USERDATA} DataType;

typedef struct DataValue {

    DataType type;

    void *value;

    int ref_count;

} DataValue;

DataValue *datavalue_create(DataType type, void *value);

void datavalue_destroy(DataValue *value);

DataValue *datavalue_incr_ref(DataValue *value);

void *datavalue_decr_ref(DataValue *value);

#endif
