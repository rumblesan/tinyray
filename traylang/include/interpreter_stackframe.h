#ifndef INTERPRETER_STACKFRAME_H
#define INTERPRETER_STACKFRAME_H

#include "bclib/hashmap.h"
#include "bclib/bstrlib.h"

typedef struct StackFrame {

    Hashmap *variables;

} StackFrame;

StackFrame *stackframe_create();

void stackframe_destroy(StackFrame *stackframe);

#endif
