#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#include "core/collections/shape_list.h"

#include "core/shapes.h"

ShapeList shape_list_element() {

    ShapeList list = malloc(sizeof(ShapeListEl));

    list->head = NULL;
    list->tail = NULL;

    return list;
}

ShapeList shape_list_empty() {
    return shape_list_element();
}

ShapeList shape_list_create(int count, ...) {

    va_list args;
    va_start (args, count);
    int i;

    Shape add_shape;
    ShapeList head;
    ShapeList tail = shape_list_empty();

    for (i = 0; i < count; i++) {
        head = shape_list_element();
        add_shape = va_arg(args, Shape);
        head->head = add_shape;
        head->tail = tail;
        tail = head;
    }

    return head;
}

void shape_list_cleanup(ShapeList list) {
    if (list->tail != NULL) {
        shape_list_cleanup(list->tail);
    }
    if (list->head != NULL) {
        shape_cleanup(list->head);
    }
    free(list);
}

ShapeList shape_list_add(ShapeList list, int count, ...) {

    va_list args;
    va_start (args, count);
    int i;

    Shape add_shape;
    ShapeList head;
    ShapeList tail = list;

    for (i = 0; i < count; i++) {
        head = shape_list_element();
        add_shape = va_arg(args, Shape);
        head->head = add_shape;
        head->tail = tail;
        tail = head;
    }

    return head;
}

Shape shape_list_head(ShapeList list) {
    return list->head;
}

ShapeList shape_list_tail(ShapeList list) {
    return list->tail;
}

bool shape_list_is_empty(ShapeList list) {
    if (list->tail == NULL) {
        return true;
    } else {
        return false;
    }
}

int shape_list_length(ShapeList list) {
    ShapeList l = list;
    int i = 0;
    while(!shape_list_is_empty(l)) {
        i += 1;
        l = shape_list_tail(l);
    }
    return i;
}

