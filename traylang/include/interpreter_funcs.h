#ifndef INTERPRETER_FUNCS_H
#define INTERPRETER_FUNCS_H

#include "interpreter.h"
#include "ast.h"
#include "object.h"
#include "bclib/list.h"
#include "bclib/bstrlib.h"

void interpreter_set_debug(Interpreter *interpreter, int debug_value);

void interpreter_error(Interpreter *interpreter, bstring err_message);

Interpreter *interpreter_enter_scope(Interpreter *interpreter);

Interpreter *interpreter_leave_scope(Interpreter *interpreter);

Object *interpreter_set_global(Interpreter *interpreter, bstring name, Object *value);

Object *interpreter_set_variable(Interpreter *interpreter, bstring name, Object *value);

Object *interpreter_get_variable(Interpreter *interpreter, bstring name);

Object *interpreter_stack_push(Interpreter *interpreter, Object *value);

Object *interpreter_stack_pop(Interpreter *interpreter);

Object *interpret(Interpreter *interpreter, Block *block);

Object *interpret_block(Interpreter *interpreter, Block *block);

Object *interpret_element(Interpreter *interpreter, Element *element);

Object *interpret_vardef(Interpreter *interpreter, VarDefinition *vardef);

Object *interpret_application(Interpreter *interpreter, Application *application);

Object *interpret_call_function(Interpreter *interpreter, bstring name, int arg_num);

Object *get_obj(Interpreter *interpreter);

Object *interpret_expression(Interpreter *interpreter, Expression *expression);

Object *interpret_number(Interpreter *interpreter, Number *number);

Object *interpret_string(Interpreter *interpreter, String *string);

#endif
