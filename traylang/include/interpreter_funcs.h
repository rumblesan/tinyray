#ifndef INTERPRETER_FUNCS_H
#define INTERPRETER_FUNCS_H

#include "interpreter.h"
#include "ast.h"
#include "datavalue.h"
#include "bclib/list.h"
#include "bclib/bstrlib.h"

void interpreter_set_debug(Interpreter *interpreter, int debug_value);

void interpreter_error(Interpreter *interpreter, bstring err_message);

DataValue *interpreter_set_variable(Interpreter *interpreter, bstring name, DataValue *value);

DataValue *interpreter_get_variable(Interpreter *interpreter, bstring name);

DataValue *interpreter_stack_push(Interpreter *interpreter, DataValue *value);

DataValue *interpreter_stack_pop(Interpreter *interpreter);

DataValue *interpret(Interpreter *interpreter, Block *block);

DataValue *interpret_block(Interpreter *interpreter, Block *block);

DataValue *interpret_element(Interpreter *interpreter, Element *element);

DataValue *interpret_vardef(Interpreter *interpreter, VarDefinition *vardef);

DataValue *interpret_application(Interpreter *interpreter, Application *application);

DataValue *interpret_call_function(Interpreter *interpreter, bstring name, int arg_num);

void *get_arg(Interpreter *interpreter);

DataValue *interpret_expression(Interpreter *interpreter, Expression *expression);

DataValue *interpret_number(Interpreter *interpreter, Number *number);

DataValue *interpret_string(Interpreter *interpreter, String *string);

#endif
