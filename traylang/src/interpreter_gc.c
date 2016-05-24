#include "dbg.h"

#include "interpreter_gc.h"

#include "interpreter.h"
#include "object.h"

#include "bclib/list.h"
#include "bclib/stack.h"

void interpreter_gc(Interpreter *interpreter) {
    interpreter_gc_mark(interpreter);
    interpreter_gc_sweep(interpreter);
}

void interpreter_gc_mark(Interpreter *interpreter) {
    STACK_FOREACH(interpreter->call_stack, el) {
        object_mark(el->value);
    }
}

void interpreter_gc_sweep(Interpreter *interpreter) {
    Object *obj;
    LIST_FOREACH(interpreter->objects, first, next, el) {
        obj = el->value;
        if (obj->marked == 0) {
            list_remove(interpreter->objects, el);
            object_destroy(obj);
        }
    }
}



