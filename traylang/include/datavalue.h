#ifndef TRAYLANG_DATAVALUE_H
#define TRAYLANG_DATAVALUE_H

typedef enum {CAMERA, COLOUR, CONFIG, FUNCTION, LIGHT, LIST, NOTHING, NUMBER, SCENE, SHAPE, TEXTURE, VECTOR } DataType;

typedef struct DataValue {

    DataType type;

    void *value;

} DataValue;

DataValue *datavalue_create(DataType type, void *value);

#endif
