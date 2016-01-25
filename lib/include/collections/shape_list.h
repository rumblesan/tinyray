#ifndef SHAPE_LIST_H
#define SHAPE_LIST_H

#include <stdbool.h>

#include "shapes.h"

struct ShapeList;

typedef struct ShapeList {

    Shape *head;

    struct ShapeList *tail;

} ShapeList;

ShapeList *shape_list_element();

ShapeList *shape_list_empty();

ShapeList *shape_list_create(int count, ...);

void shape_list_cleanup(ShapeList *list);

ShapeList *shape_list_add(ShapeList *list, int count, ...);

Shape *shape_list_head(ShapeList *list); 

ShapeList *shape_list_tail(ShapeList *list); 

bool shape_list_is_empty(ShapeList *list);

int shape_list_length(ShapeList *list); 

#endif
