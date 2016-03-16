#include <stdlib.h>

#include "dbg.h"

#include "interpreter.h"
#include "ast.h"
#include "ast-print.h"

#include "lights.h"
#include "colours.h"

#include "bclib/hashmap.h"
#include "bclib/list.h"
#include "bclib/bstrlib.h"

DataValue *datavalue_create(DataType type, void *value) {
    DataValue *data_value = malloc(sizeof(DataValue));

    check_mem(data_value);
    data_value->type = type;
    data_value->value = value;

    return data_value;
error:
    return NULL;
}


Interpreter *interpreter_create() {
    Interpreter *interpreter = malloc(sizeof(Interpreter));
    check_mem(interpreter);

    Hashmap *variables = hashmap_create(NULL, NULL);
    check_mem(variables);

    interpreter->error = 0;
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
            // TODO
            // delete datavalues stored in hashmap
            hashmap_destroy(interpreter->variables);
        }
        free(interpreter);
    }
}

void interpreter_error(Interpreter *interpreter, bstring err_message) {
    interpreter->error = 1;
    interpreter->err_message = err_message;
}

DataValue *interpreter_set_variable(Interpreter *interpreter, bstring name, DataValue *value) {
    debug("Set variable: %s", name->data);
    check(name, "NULL key passed for variable name");
    check(value, "NULL value passed for variable value: %s", name->data);
    int result = hashmap_set(interpreter->variables, name, value);
    check(result == 0, "Could not set value in variables hashmap");
    return value;
error:
    interpreter_error(interpreter, bfromcstr("Could not set variable"));
    return NULL;
}

DataValue *interpreter_get_variable(Interpreter *interpreter, bstring name) {
    debug("Get variable: %s", name->data);
    check(name, "NULL key passed for variable name");
    DataValue *value = hashmap_get(interpreter->variables, name);
    check(value, "Could not get variable: %s", name->data);
    return value;
error:
    interpreter_error(interpreter, bfromcstr("Could not get variable"));
    return NULL;
}

DataValue *interpret(Interpreter *interpreter, Block *block) {
    return interpret_block(interpreter, block);
}

DataValue *interpret_block(Interpreter *interpreter, Block *block) {
    DataValue *return_val = NULL;
    LIST_FOREACH(block->elements, first, next, cur) {
        return_val = interpret_element(interpreter, cur->value);
        check(return_val, "Error interpreting element");
        check(interpreter->error != 1, "Error whilst interpreting");
    }
    return return_val;
error:
    return NULL;
}

DataValue *interpret_element(Interpreter *interpreter, Element *element) {
    switch(element->elementType) {
        case VARDEFINITIONEL: return interpret_vardef(interpreter, element->varDefinition); break;
        case APPLICATIONEL:   return interpret_application(interpreter, element->application); break;
    }
}

DataValue *interpret_vardef(Interpreter *interpreter, VarDefinition *vardef) {
    DataValue *expr_value = interpret_expression(interpreter, vardef->expression);
    check(interpreter->error != 1, "Error interpreting vardef");
    check(expr_value, "Error evaluating vardef");
    interpreter_set_variable(interpreter, vardef->name, expr_value);
    check(interpreter->error != 1, "Error interpreting vardef");
    return expr_value;
error:
    if (interpreter->error == 0) {
        interpreter_error(interpreter, bfromcstr("Error interpreting vardef"));
    }
    return NULL;
}

DataValue *interpret_application(Interpreter *interpreter, Application *application) {
    List *arg_values = list_create();
    DataValue *val;
    LIST_FOREACH(application->args, first, next, cur) {
        val = interpret_expression(interpreter, cur->value);
        check(interpreter->error != 1, "Error whilst interpreting");
        list_unshift(arg_values, val);
    }
    DataValue *result = interpret_call_function(interpreter, application->name, arg_values);
    check(interpreter->error != 1, "Error whilst interpreting");
    // TODO
    // clearing up argument lists could probably be handled better...
    list_destroy(arg_values);
    return result;
error:
    return NULL;
}

DataValue *interpret_call_function(Interpreter *interpreter, bstring name, List *args) {
    DataValue *func_data = interpreter_get_variable(interpreter, name);
    check(interpreter->error != 1, "Error whilst calling function");
    func_cb f = func_data->value;
    return f(args);
error:
    return NULL;
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
    DataValue *dv = datavalue_create(NUMBER, number);
    check(dv != NULL, "Could not create datavalue")
    return dv;
error:
    if (interpreter->error == 0) {
        interpreter_error(interpreter, bfromcstr("Error whilst creating number data value"));
    }
    return NULL;
}

