#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "bclib/hashmap.h"
#include "bclib/stack.h"
#include "bclib/list.h"
#include "bclib/bstrlib.h"

#define INITIAL_GC_THRESHOLD 20

typedef struct Interpreter {

    int error;

    bstring err_message;

    int debug_mode;

    Stack *call_stack;

    Stack *scopes;

    List *objects;

    int max_objects;

    Hashmap *globals;

} Interpreter;

Interpreter *interpreter_create();

#endif
