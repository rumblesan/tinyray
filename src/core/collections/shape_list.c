#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "core/shapes.h"
#include "core/collections/shape_list.h"

ShapeList shape_list_create() {

    ShapeList list = (ShapeList) malloc(sizeof(ShapeListEl));

    list->head = NULL;
    list->tail = NULL;

    return list;
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

ShapeList shape_list_add(ShapeList list, Shape shape) {

    ShapeList new_head = shape_list_create();

    new_head->head = shape;
    new_head->tail = list;

    return new_head;
}

Shape shape_list_head(ShapeList list) {
    return list->head;
}

ShapeList shape_list_tail(ShapeList list) {
    return list->tail;
}

bool shape_list_empty(ShapeList list) {
    if (list->tail == NULL) {
        return true;
    } else {
        return false;
    }
}

int shape_list_length(ShapeList list) {
    ShapeList l = list;
    int i = 0;
    while(!shape_list_empty(l)) {
        i += 1;
        l = shape_list_tail(l);
    }
    return i;
}

