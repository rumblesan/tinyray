#include <stdlib.h>

#include "dbg.h"

#include "interpreter.h"

#include "bclib/hashmap.h"
#include "bclib/stack.h"
#include "bclib/list.h"
#include "bclib/bstrlib.h"

Interpreter *interpreter_create() {
    Interpreter *interpreter = malloc(sizeof(Interpreter));
    check_mem(interpreter);

    Hashmap *variables = hashmap_create(NULL, NULL);
    check_mem(variables);

    Stack *call_stack = stack_create();
    check_mem(call_stack);

    List *objects = list_create();
    check_mem(objects);

    interpreter->debug_mode = 0;
    interpreter->error = 0;
    interpreter->variables = variables;
    interpreter->call_stack = call_stack;
    interpreter->objects = objects;
    interpreter->max_objects = INITIAL_GC_THRESHOLD;

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
            // delete objects stored in hashmap
            hashmap_destroy(interpreter->variables);
        }
        if (interpreter->call_stack) {
            stack_clear_destroy(interpreter->call_stack);
        }
        if (interpreter->objects) {
            list_clear_destroy(interpreter->objects);
        }
        free(interpreter);
    }
}

