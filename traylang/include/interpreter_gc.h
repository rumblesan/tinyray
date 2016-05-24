#ifndef INTERPRETER_GC_H
#define INTERPRETER_GC_H

#include "interpreter.h"

void interpreter_gc(Interpreter *interpreter);

void interpreter_gc_mark(Interpreter *interpreter);

void interpreter_gc_sweep(Interpreter *interpreter);

#endif
