#ifndef TRAYLANG_DATAVALUE_H
#define TRAYLANG_DATAVALUE_H

typedef enum {FUNCTION, LIST, NOTHING, NUMBER, USERDATA} DataType;

typedef struct DataValue {

    DataType type;

    void *value;

} DataValue;

DataValue *datavalue_create(DataType type, void *value);

#endif
