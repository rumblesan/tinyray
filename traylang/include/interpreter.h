#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "datavalue.h"
#include "ast.h"
#include "bclib/hashmap.h"
#include "bclib/list.h"
#include "bclib/bstrlib.h"

typedef struct Interpreter {

    int error;

    bstring err_message;

    int debug_mode;

    Hashmap *variables;

} Interpreter;

Interpreter *interpreter_create();

void interpreter_destroy(Interpreter *interpreter);

void interpreter_set_debug(Interpreter *interpreter, int debug_value);

void interpreter_error(Interpreter *interpreter, bstring err_message);

DataValue *interpreter_set_variable(Interpreter *interpreter, bstring name, DataValue *value);

DataValue *interpreter_get_variable(Interpreter *interpreter, bstring name);

DataValue *interpret(Interpreter *interpreter, Block *block);

DataValue *interpret_block(Interpreter *interpreter, Block *block);

DataValue *interpret_element(Interpreter *interpreter, Element *element);

DataValue *interpret_vardef(Interpreter *interpreter, VarDefinition *vardef);

DataValue *interpret_application(Interpreter *interpreter, Application *application);

DataValue *interpret_call_function(Interpreter *interpreter, bstring name, List *args);

void *get_arg(List *args, int idx);

DataValue *interpret_expression(Interpreter *interpreter, Expression *expression);

DataValue *interpret_number(Interpreter *interpreter, Number *number);

DataValue *interpret_string(Interpreter *interpreter, String *string);

#endif
