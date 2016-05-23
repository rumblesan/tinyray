#include <stdlib.h>

#include "dbg.h"

#include "interpreter.h"

#include "bclib/hashmap.h"
#include "bclib/stack.h"
#include "bclib/bstrlib.h"

Interpreter *interpreter_create() {
    Interpreter *interpreter = malloc(sizeof(Interpreter));
    check_mem(interpreter);

    Hashmap *variables = hashmap_create(NULL, NULL);
    check_mem(variables);

    Stack *call_stack = stack_create();
    check_mem(call_stack);

    interpreter->debug_mode = 0;
    interpreter->error = 0;
    interpreter->variables = variables;
    interpreter->call_stack = call_stack;

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
        if (interpreter->call_stack) {
            stack_clear_destroy(interpreter->call_stack);
        }
        free(interpreter);
    }
}

