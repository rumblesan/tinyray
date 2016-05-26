#include "dbg.h"

#include "interpreter_funcs.h"

#include "interpreter.h"
#include "interpreter_stackframe.h"
#include "object.h"

#include "bclib/hashmap.h"
#include "bclib/stack.h"
#include "bclib/bstrlib.h"

void interpreter_set_debug(Interpreter *interpreter, int debug_value) {
    interpreter->debug_mode = debug_value;
}

void interpreter_error(Interpreter *interpreter, bstring err_message) {
    interpreter->error = 1;
    interpreter->err_message = err_message;
}

Interpreter *interpreter_enter_scope(Interpreter *interpreter) {
    StackFrame *stackframe = stackframe_create();
    check(stackframe, "Could not create new stackframe");
    stack_push(interpreter->scopes, stackframe);
    return interpreter;
error:
    return NULL;
}

Interpreter *interpreter_leave_scope(Interpreter *interpreter) {
    StackFrame *stackframe = stack_pop(interpreter->scopes);
    check(stackframe, "Could not leave previous scope");

    stackframe_destroy(stackframe);
    return interpreter;
error:
    return NULL;
}

Object *interpreter_set_global(Interpreter *interpreter, bstring name, Object *value) {
    if (interpreter->debug_mode) {
        debug("Set global: %s", name->data);
    }
    check(name, "NULL key passed for global name");
    check(value, "NULL value passed for global value: %s", name->data);
    int result = hashmap_set(interpreter->globals, name, value);
    check(result == 0, "Could not set value in globals hashmap");
    return value;
error:
    interpreter_error(interpreter, bfromcstr("Could not set global"));
    return NULL;
}

Object *interpreter_set_variable(Interpreter *interpreter, bstring name, Object *value) {
    if (interpreter->debug_mode) {
        debug("Set variable: %s", name->data);
    }
    check(name, "NULL key passed for variable name");
    check(value, "NULL value passed for variable value: %s", name->data);
    StackFrame *stackframe = interpreter->scopes->stack->value;
    check(stackframe, "Couldn't get stackframe");
    int result = hashmap_set(stackframe->variables, name, value);
    check(result == 0, "Could not set value in variables hashmap");
    return value;
error:
    interpreter_error(interpreter, bfromcstr("Could not set variable"));
    return NULL;
}

Object *interpreter_get_variable(Interpreter *interpreter, bstring name) {
    if (interpreter->debug_mode) {
        debug("Get variable: %s", name->data);
    }
    check(name, "NULL key passed for variable name");
    StackFrame *stackframe = interpreter->scopes->stack->value;
    check(stackframe, "Couldn't get stackframe");
    Object *value = hashmap_get(stackframe->variables, name);
    if (value == NULL) {
        value = hashmap_get(interpreter->globals, name);
    }
    check(value, "Could not get variable: %s", name->data);
    return value;
error:
    interpreter_error(interpreter, bfromcstr("Could not get variable"));
    return NULL;
}

Object *interpreter_stack_push(Interpreter *interpreter, Object *value) {
    check(value, "NULL value pushed to stack");
    Stack *stack = stack_push(interpreter->call_stack, value);
    check(stack, "Error pushing value to stack");
    return value;
error:
    interpreter_error(interpreter, bfromcstr("Error pushing value to stack"));
    return NULL;
}

Object *interpreter_stack_pop(Interpreter *interpreter) {
    Object *value = stack_pop(interpreter->call_stack);
    check(value, "Error getting value from stack");
    return value;
error:
    interpreter_error(interpreter, bfromcstr("Error getting value from stack"));
    return NULL;
}

Object *interpret(Interpreter *interpreter, Block *block) {
    return interpret_block(interpreter, block);
}

Object *interpret_block(Interpreter *interpreter, Block *block) {
    Object *return_val = NULL;
    LIST_FOREACH(block->elements, first, next, cur) {
        return_val = interpret_element(interpreter, cur->value);
        check(return_val, "Error interpreting element");
        check(interpreter->error != 1, "Error whilst interpreting");
    }
    return return_val;
error:
    return NULL;
}

Object *interpret_element(Interpreter *interpreter, Element *element) {
    switch(element->elementType) {
        case VARDEFINITIONEL: return interpret_vardef(interpreter, element->varDefinition); break;
        case APPLICATIONEL:   return interpret_application(interpreter, element->application); break;
    }
}

Object *interpret_vardef(Interpreter *interpreter, VarDefinition *vardef) {
    Object *expr_value = interpret_expression(interpreter, vardef->expression);
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

Stack *interpreter_push_args(Interpreter *interpreter, Application *application) {
    Object *val;
    // Iterate list in reverse so first arg is highest on stack
    LIST_FOREACH(application->args, last, prev, cur) {
        val = interpret_expression(interpreter, cur->value);
        interpreter_stack_push(interpreter, val);
        check(interpreter->error != 1, "Error whilst interpreting");
    }
    return interpreter->call_stack;
error:
    return NULL;
}

Object *interpret_application(Interpreter *interpreter, Application *application) {
    int arg_num = list_count(application->args);
    if (interpreter->debug_mode) {
        debug("Application: %s", application->name->data);
        debug("Arg num: %d", arg_num);
    }
    Stack *stack = interpreter_push_args(interpreter, application);
    check(stack, "Error whilst pushing args to stack");
    Object *result = interpret_call_function(interpreter, application->name, arg_num);
    check(interpreter->error != 1, "Error whilst interpreting");
    return result;
error:
    return NULL;
}

Object *interpret_call_function(Interpreter *interpreter, bstring name, int arg_num) {
    Object *func_obj = interpreter_get_variable(interpreter, name);
    check(interpreter->error != 1, "Error whilst calling function");
    c_func f = func_obj->cfunction;
    interpreter_enter_scope(interpreter);
    Object *result = f(interpreter, arg_num);
    interpreter_leave_scope(interpreter);
    return result;
error:
    return NULL;
}

Object *get_obj(Interpreter *interpreter) {
    return interpreter_stack_pop(interpreter);
}

Object *interpret_expression(Interpreter *interpreter, Expression *expression) {
    Object *v = NULL;
    switch(expression->expressionType) {
        case APPLICATIONEXPR:
            if (interpreter->debug_mode) {
                debug("interpret application");
            }
            v = interpret_application(interpreter, expression->application);
            break;
        case NUMBEREXPR:
            if (interpreter->debug_mode) {
                debug("interpret number");
            }
            v = interpret_number(interpreter, expression->number);
            break;
        case STRINGEXPR:
            if (interpreter->debug_mode) {
                debug("interpret string");
            }
            v = interpret_string(interpreter, expression->string);
            break;
        case VARIABLEEXPR:
            if (interpreter->debug_mode) {
                debug("interpret variable");
            }
            v = interpreter_get_variable(interpreter, expression->variable->name);
            break;
    }
    return v;
}

Object *interpret_number(Interpreter *interpreter, Number *number) {
    Object *dv = object_number(interpreter, number->value);
    check(dv != NULL, "Could not create object")
    return dv;
error:
    if (interpreter->error == 0) {
        interpreter_error(interpreter, bfromcstr("Error whilst creating number object"));
    }
    return NULL;
}

Object *interpret_string(Interpreter *interpreter, String *string) {
    Object *dv = object_string(interpreter, string->value);
    check(dv != NULL, "Could not create object")
    return dv;
error:
    if (interpreter->error == 0) {
        interpreter_error(interpreter, bfromcstr("Error whilst creating number object"));
    }
    return NULL;
}

