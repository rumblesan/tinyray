#include <stdlib.h>

#include "dbg.h"

#include "interpreter.h"
#include "interpreter_gc.h"
#include "object.h"
#include "ast.h"
#include "bclib/list.h"

Object *object_create(Interpreter *interpreter) {
    if (list_count(interpreter->objects) == interpreter->max_objects) {
        interpreter_gc(interpreter);
    }
    Object *obj = malloc(sizeof(Object));
    check_mem(obj);
    obj->marked = 0;
    list_push(interpreter->objects, obj);
    return obj;
error:
    return NULL;
}

LambdaObject *lambda_create(List *arg_names, Block *body) {
    LambdaObject *lambda = malloc(sizeof(LambdaObject));
    check_mem(lambda);
    lambda->arg_names = arg_names;
    lambda->body = body;
    return lambda;
error:
    return NULL;
}

void lambda_destroy(LambdaObject *lambda) {
    bstring name;
    LIST_FOREACH(lambda->arg_names, first, next, el) {
        name = el->value;
        bdestroy(name);
    }
    list_destroy(lambda->arg_names);
    // AST section is destroyed when the interpreter quits
    free(lambda);
}

void object_list_destroy(List *list) {
    Object *obj;
    LIST_FOREACH(list, first, next, el) {
        obj = el->value;
        object_destroy(obj);
    }
    list_destroy(list);
}

Object *object_c_function(Interpreter *interpreter, c_func func) {
    Object *object = object_create(interpreter);
    object->type = CFUNCTION;
    object->cfunction = func;
    return object;
}

Object *object_lambda(Interpreter *interpreter, List *arg_names, Block *body) {
    Object *object = object_create(interpreter);
    object->type = LAMBDA;
    LambdaObject *lambda = lambda_create(arg_names, body);
    object->lambda = lambda;
    return object;
}

Object *object_list(Interpreter *interpreter, List *list) {
    Object *object = object_create(interpreter);
    object->type = LIST;
    object->list = list;
    return object;
}

Object *object_nothing(Interpreter *interpreter) {
    Object *object = object_create(interpreter);
    object->type = NOTHING;
    return object;
}

Object *object_number(Interpreter *interpreter, double num) {
    Object *object = object_create(interpreter);
    object->type = NUMBER;
    object->number = num;
    return object;
}

Object *object_string(Interpreter *interpreter, bstring string) {
    Object *object = object_create(interpreter);
    object->type = STRING;
    object->string = string;
    return object;
}

Object *object_cdata(Interpreter *interpreter, void *cdata) {
    Object *object = object_create(interpreter);
    object->type = CDATA;
    object->cdata = cdata;
    return object;
}

void object_destroy(Object *object) {
    switch(object->type) {
        case CFUNCTION:
            debug("Not freeing up c function pointer");
            break;
        case LAMBDA:
            lambda_destroy(object->lambda);
            break;
        case LIST:
            object_list_destroy(object->list);
            break;
        case NOTHING:
            debug("Not freeing up Nothing");
            break;
        case NUMBER:
            debug("No need to free number");
            break;
        case STRING:
            bdestroy(object->string);
            break;
        case CDATA:
            debug("Not freeing up CData");
            break;
    }
    free(object);
}

void object_mark(Object *object) {
    if (object->marked == 1) {
        return;
    }
    object->marked = 1;
    if (object->type == LIST) {
        List *list = object->list;
        LIST_FOREACH(list, first, next, el) {
            object_mark(el->value);
        }
    }
}
