#include <stdlib.h>

#include "dbg.h"

#include "language/interpreter.h"
#include "language/ast.h"
#include "language/ast-print.h"

#include "lights.h"
#include "colours.h"

#include "bclib/hashmap.h"
#include "bclib/list.h"
#include "bclib/bstrlib.h"

DataValue *datavalue_create(DataType type, void *value) {
    DataValue *data_value = malloc(sizeof(DataValue));

    data_value->type = type;
    data_value->value = value;

    return data_value;
}


Interpreter *interpreter_create() {
    Interpreter *interpreter = malloc(sizeof(Interpreter));
    check_mem(interpreter);

    Hashmap *variables = hashmap_create(NULL, NULL);
    check_mem(variables);

    interpreter->variables = variables;

    return interpreter;
error:
    if (interpreter) {
        interpreter_destroy(interpreter);
    }
    return NULL;
}

void interpreter_destroy(Interpreter *interpreter) {
    if (interpreter) {
        if (interpreter->variables) {
            hashmap_destroy(interpreter->variables);
        }
        free(interpreter);
    }
}

void interpreter_set_variable(Interpreter *interpreter, bstring name, DataValue *value) {
    debug("Set variable: %s", name->data);
    hashmap_set(interpreter->variables, name, value);
}

DataValue *interpreter_get_variable(Interpreter *interpreter, bstring name) {
    debug("Get variable: %s", name->data);
    DataValue *value = hashmap_get(interpreter->variables, name);
    return value;
}

DataValue *interpret(Interpreter *interpreter, Block *block) {
    debug("Interpreting");
    return interpret_block(interpreter, block);
}

DataValue *interpret_block(Interpreter *interpreter, Block *block) {
    debug("Block");

    DataValue *returnVal;

    LIST_FOREACH(block->elements, first, next, cur) {
        returnVal = interpret_element(interpreter, cur->value);
    }
    return returnVal;
}

DataValue *interpret_element(Interpreter *interpreter, Element *element) {
    switch(element->elementType) {
        case VARDEFINITIONEL: return interpret_vardef(interpreter, element->varDefinition); break;
        case APPLICATIONEL:   return interpret_application(interpreter, element->application); break;
    }
}

DataValue *interpret_vardef(Interpreter *interpreter, VarDefinition *vardef) {
    DataValue *expr_value = interpret_expression(interpreter, vardef->expression);
    interpreter_set_variable(interpreter, vardef->name, expr_value);
    return expr_value;
}

DataValue *interpret_application(Interpreter *interpreter, Application *application) {
    debug("Application");
    List *arg_values = list_create();
    DataValue *val;
    LIST_FOREACH(application->args, first, next, cur) {
        val = interpret_expression(interpreter, cur->value);
        list_unshift(arg_values, val);
    }
    DataValue *result = interpret_call_function(interpreter, application->name, arg_values);
    list_destroy(arg_values);
    return result;
}

DataValue *interpret_call_function(Interpreter *interpreter, bstring name, List *args) {
    debug("Calling function %s", name->data);
    DataValue *func_data = interpreter_get_variable(interpreter, name);
    func_cb f = func_data->value;
    return f(args);
}

void *get_arg(List *args, int idx) {
    DataValue *dv = list_get(args, idx);
    return dv != NULL ? dv->value : NULL;
}

DataValue *interpret_expression(Interpreter *interpreter, Expression *expression) {
    switch(expression->expressionType) {
        case APPLICATIONEXPR: return interpret_application(interpreter, expression->application); break;
        case NUMBEREXPR:      return interpret_number(interpreter, expression->number); break;
        case VARIABLEEXPR:    return interpreter_get_variable(interpreter, expression->variable->name); break;
    }
}

DataValue *interpret_number(Interpreter *interpreter, Number *number) {
    debug("Number: %f", number->value);
    return datavalue_create(NUMBER, number);
}


