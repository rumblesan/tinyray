#include <stdlib.h>

#include "dbg.h"
#include "object.h"

Object *object_create(ObjectType type, void *value) {
    Object *obj = malloc(sizeof(Object));
    check_mem(obj);
    obj->type = type;
    obj->value = value;
    return obj;
error:
    return NULL;
}

Object *object_function(func_cb func) {
    return object_create(FUNCTION, func);
}

Object *object_list(List *list) {
    return object_create(LIST, list);
}

Object *object_nothing() {
    return object_create(NOTHING, NULL);
}

Object *object_number(double num) {
    double *val = malloc(sizeof(double));
    *val = num;
    return object_create(NUMBER, val);
}

Object *object_string(bstring string) {
    return object_create(STRING, string);
}

Object *object_cdata(void *cdata) {
    return object_create(CDATA, cdata);
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

