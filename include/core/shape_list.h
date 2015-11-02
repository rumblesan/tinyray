#ifndef SHAPE_LIST_H
#define SHAPE_LIST_H

#include "core/shapes.h"

typedef struct shape_list_el *ShapeList;
typedef struct shape_list_el {

    Shape head;

    ShapeList tail;

} ShapeListEl;

ShapeList shape_list_create();

void shape_list_cleanup(ShapeList list);

ShapeList shape_list_add(ShapeList list, Shape shape);

Shape shape_list_head(ShapeList list); 

ShapeList shape_list_tail(ShapeList list); 

int shape_list_length(ShapeList list); 

#endif
