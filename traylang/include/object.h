#ifndef TRAYLANG_OBJECT_H
#define TRAYLANG_OBJECT_H

#include "interpreter.h"
#include "bclib/list.h"
#include "bclib/bstrlib.h"

typedef enum {FUNCTION, LIST, NOTHING, NUMBER, STRING, CDATA} ObjectType;

typedef struct Object {

    ObjectType type;

    void *value;

} Object;

typedef Object *(*func_cb)(Interpreter *interpreter, int arg_count);

Object *object_function(func_cb func);

Object *object_list(List *list);

Object *object_nothing();

Object *object_number(double number);

Object *object_string(bstring string);

Object *object_cdata(void *cdata);

void object_destroy(Object *object);

void object_clear_destroy(Object *object);

#endif
