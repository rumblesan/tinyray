#include <stdlib.h>

#include "dbg.h"

#include "interpreter_stackframe.h"

#include "bclib/hashmap.h"
#include "bclib/bstrlib.h"

StackFrame *stackframe_create() {
    StackFrame *stackframe = malloc(sizeof(StackFrame));
    check_mem(stackframe);

    Hashmap *variables = hashmap_create(NULL, NULL);
    check_mem(variables);

    stackframe->variables = variables;

    return stackframe;
error:
    if (stackframe) {
        stackframe_destroy(stackframe);
    }
    return NULL;
}

void stackframe_destroy(StackFrame *stackframe) {
    if (stackframe->variables) {
        hashmap_destroy(stackframe->variables);
    }
    free(stackframe);
}

