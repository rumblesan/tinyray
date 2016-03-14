#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "language/ast.h"
#include "bclib/hashmap.h"
#include "bclib/list.h"
#include "bclib/bstrlib.h"

typedef enum {CAMERA, CANVAS, COLOUR, CONFIG, LIGHT, RAY, SCENE, SHAPE, TEXTURE, VECTOR, NUMBER, FUNCTION, NOTHING} DataType;

typedef struct DataValue {

    DataType type;

    void *value;

} DataValue;

DataValue *datavalue_create(DataType type, void *value);

typedef DataValue *(*func_cb)(List *args);

typedef struct Interpreter {

    Hashmap *variables;

} Interpreter;

Interpreter *interpreter_create();

void interpreter_destroy(Interpreter *interpreter);

void interpreter_set_variable(Interpreter *interpreter, bstring name, DataValue *value);

DataValue *interpreter_get_variable(Interpreter *interpreter, bstring name);

DataValue *interpret(Interpreter *interpreter, Block *block);

DataValue *interpret_block(Interpreter *interpreter, Block *block);

DataValue *interpret_element(Interpreter *interpreter, Element *element);

DataValue *interpret_vardef(Interpreter *interpreter, VarDefinition *vardef);

DataValue *interpret_application(Interpreter *interpreter, Application *application);

DataValue *interpret_call_function(Interpreter *interpreter, bstring name, List *args);

DataValue *interpret_expression(Interpreter *interpreter, Expression *expression);

DataValue *interpret_number(Interpreter *interpreter, Number *number);

#endif
