#ifndef TRAYLANG_OBJECT_H
#define TRAYLANG_OBJECT_H

#include "interpreter.h"
#include "bclib/list.h"
#include "bclib/bstrlib.h"

typedef enum {CFUNCTION, LIST, NOTHING, NUMBER, STRING, CDATA} ObjectType;

typedef struct Object {

    ObjectType type;

    unsigned char marked;

    void *value;

} Object;

typedef Object *(*c_func)(Interpreter *interpreter, int arg_count);

Object *object_c_function(Interpreter *interpreter, c_func func);

Object *object_list(Interpreter *interpreter, List *list);

Object *object_nothing(Interpreter *interpreter);

Object *object_number(Interpreter *interpreter, double number);

Object *object_string(Interpreter *interpreter, bstring string);

Object *object_cdata(Interpreter *interpreter, void *cdata);

void object_destroy(Object *object);

void object_clear_destroy(Object *object);

void object_mark(Object *object);

#endif
