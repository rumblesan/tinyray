#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "bclib/hashmap.h"
#include "bclib/stack.h"
#include "bclib/bstrlib.h"

typedef struct Interpreter {

    int error;

    bstring err_message;

    int debug_mode;

    Stack *call_stack;

    Hashmap *variables;

} Interpreter;

Interpreter *interpreter_create();

void interpreter_destroy(Interpreter *interpreter);

#endif
