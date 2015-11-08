#include <stdio.h>
#include <stdbool.h>

#include "tests/min_unit.h"

#include "core/shapes.h"
#include "core/collections/shape_list.h"

static char * test_creation() {

    Shape shape = sphere_create(vector3d(1.0, 2.0, 3.0), 1.0, colour(0, 0, 0));
    ShapeList list = shape_list_add(shape_list_create(), shape);

    mu_assert("Error: ShapeList not created correctly", list->head->type == SPHERE);

    shape_list_cleanup(list);
    return 0;
}

static char * test_length() {
    Colour c = colour(0, 0, 0);
    ShapeList empty = shape_list_create();
    mu_assert("Error: ShapeList should be empty", shape_list_empty(empty) == true);
    ShapeList list1 = shape_list_add(empty, sphere_create(vector3d(1.0, 2.0, 3.0), 1.0, c));
    ShapeList list2 = shape_list_add(list1, sphere_create(vector3d(1.0, 2.0, 3.0), 1.0, c));
    ShapeList list3 = shape_list_add(list2, sphere_create(vector3d(1.0, 2.0, 3.0), 1.0, c));
    ShapeList list4 = shape_list_add(list3, sphere_create(vector3d(1.0, 2.0, 3.0), 1.0, c));

    int len = shape_list_length(list4);

    mu_assert("Error: ShapeList is not empty", shape_list_empty(list4) == false);
    mu_assert("Error: ShapeList length not correct", len == 4);

    shape_list_cleanup(list4);
    return 0;
}

char * test_shape_list() {
    mu_run_test(test_creation);
    mu_run_test(test_length);
    return 0;
}


