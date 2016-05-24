#include "dbg.h"

#include "interpreter_gc.h"

#include "interpreter.h"
#include "object.h"

#include "bclib/list.h"
#include "bclib/stack.h"
#include "bclib/hashmap.h"
#include "bclib/bstrlib.h"

void interpreter_gc(Interpreter *interpreter) {
    int ocount = list_count(interpreter->objects);
    interpreter_gc_mark(interpreter);
    interpreter_gc_sweep(interpreter);
    int new_max = list_count(interpreter->objects) * 2;
    if (new_max < INITIAL_GC_THRESHOLD) {
        new_max = INITIAL_GC_THRESHOLD;
    }
    interpreter->max_objects = new_max;
    if (interpreter->debug_mode) {
        debug("%d objects reduced to %d", ocount, list_count(interpreter->objects));
    }
}

int mark_variable(HashmapNode *node) {
    Object *obj = node->data;
    object_mark(obj);
    return 0;
}

void interpreter_gc_mark(Interpreter *interpreter) {
    if (interpreter->debug_mode) {
        debug("Marking stack");
    }
    STACK_FOREACH(interpreter->call_stack, el) {
        object_mark(el->value);
    }
    if (interpreter->debug_mode) {
        debug("Marking variables");
    }
    hashmap_traverse(interpreter->variables, mark_variable);
}

void interpreter_gc_sweep(Interpreter *interpreter) {
    if (interpreter->debug_mode) {
        debug("Sweeping");
    }
    List *objects = interpreter->objects;
    ListNode *node = objects->first;
    ListNode *next_node;
    Object *obj;
    while(node) {
        next_node = node->next;
        obj = node->value;

        if (obj->marked == 0) {
            if (node == objects->first) {
                objects->first = node->next;
            }
            if (node == objects->last) {
                objects->last = node->prev;
            }
            if (node->prev) {
                node->prev->next = node->next;
            }
            if (node->next) {
                node->next->prev = node->prev;
            }
            object_destroy(obj);
            free(node);
            objects->length -= 1;
        }

        node = next_node;
    }
}

