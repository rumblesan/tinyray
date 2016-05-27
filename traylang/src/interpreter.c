#include <stdlib.h>

#include "dbg.h"

#include "interpreter.h"
#include "interpreter_stackframe.h"

#include "bclib/hashmap.h"
#include "bclib/stack.h"
#include "bclib/list.h"
#include "bclib/bstrlib.h"

Interpreter *interpreter_create() {
    Interpreter *interpreter = malloc(sizeof(Interpreter));
    check_mem(interpreter);

    Hashmap *globals = hashmap_create(NULL, NULL);
    check_mem(globals);

    Stack *call_stack = stack_create();
    check_mem(call_stack);

    Stack *scopes = stack_create();
    check_mem(scopes);
    StackFrame *stackframe = stackframe_create();
    check_mem(stackframe);
    stack_push(scopes, stackframe);

    List *objects = list_create();
    check_mem(objects);

    interpreter->debug_mode = 0;
    interpreter->error = 0;
    interpreter->globals = globals;
    interpreter->call_stack = call_stack;
    interpreter->scopes = scopes;
    interpreter->objects = objects;
    interpreter->max_objects = INITIAL_GC_THRESHOLD;

    return interpreter;
error:
    return NULL;
}

