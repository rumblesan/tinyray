#include <stdlib.h>

#include "dbg.h"

#include "interpreter.h"
#include "object.h"
#include "bclib/list.h"

Object *object_create(Interpreter *interpreter, ObjectType type, void *value) {
    Object *obj = malloc(sizeof(Object));
    check_mem(obj);
    obj->type = type;
    obj->value = value;
    list_push(interpreter->objects, obj);
    return obj;
error:
    return NULL;
}

Object *object_function(Interpreter *interpreter, func_cb func) {
    return object_create(interpreter, FUNCTION, func);
}

Object *object_list(Interpreter *interpreter, List *list) {
    return object_create(interpreter, LIST, list);
}

Object *object_nothing(Interpreter *interpreter) {
    return object_create(interpreter, NOTHING, NULL);
}

Object *object_number(Interpreter *interpreter, double num) {
    double *val = malloc(sizeof(double));
    *val = num;
    return object_create(interpreter, NUMBER, val);
}

Object *object_string(Interpreter *interpreter, bstring string) {
    return object_create(interpreter, STRING, string);
}

Object *object_cdata(Interpreter *interpreter, void *cdata) {
    return object_create(interpreter, CDATA, cdata);
}

void object_destroy(Object *object) {
    free(object);
}

void object_clear_destroy(Object *object) {
    switch(object->type) {
        case FUNCTION:
            debug("Not freeing up function pointer");
            break;
        case LIST:
            list_clear_destroy(object->value);
            break;
        case NOTHING:
            debug("Not freeing up Nothing");
            break;
        case NUMBER:
            free(object->value);
            break;
        case STRING:
            bdestroy(object->value);
            break;
        case CDATA:
            debug("Not freeing up CData");
            break;
    }
    free(object);
}

