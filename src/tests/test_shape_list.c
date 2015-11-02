#include <stdio.h>

#include "tests/min_unit.h"

#include "core/shapes.h"
#include "core/coordinates.h"
#include "core/shape_list.h"

static char * test_creation() {

    Coord3D centre = coord3d_create(1.0, 1.0, 1.0);
    Shape shape = sphere_create(centre, 1.0);
    ShapeList list = shape_list_add(shape_list_create(), shape);

    mu_assert("Error: ShapeList not created correctly", list->head->type == SPHERE);

    shape_cleanup(shape);
    coord3d_cleanup(centre);
    return 0;
}

static char * test_length() {
    Coord3D centre = coord3d_create(1.0, 1.0, 1.0);
    ShapeList list1 = shape_list_add(shape_list_create(), sphere_create(centre, 1.0));
    ShapeList list2 = shape_list_add(list1, sphere_create(centre, 1.0));
    ShapeList list3 = shape_list_add(list2, sphere_create(centre, 1.0));
    ShapeList list4 = shape_list_add(list3, sphere_create(centre, 1.0));

    int len = shape_list_length(list4);

    mu_assert("Error: ShapeList length not correct", len == 4);

    coord3d_cleanup(centre);
    return 0;
}

char * test_shape_list() {
    mu_run_test(test_creation);
    mu_run_test(test_length);
    return 0;
}


