#include <stdio.h>
#include <stdbool.h>

#include "tests/min_unit.h"

#include "core/shapes.h"
#include "core/collections/shape_list.h"
#include "core/textures.h"

static char * test_creation() {

    Texture t = texture_flat(0.5, colour(0, 0, 0));
    Shape shape = sphere_create(vector3d(1.0, 2.0, 3.0), 1.0, t);
    ShapeList list = shape_list_create(1, shape);

    mu_assert("Error: ShapeList not created correctly", list->head->type == SPHERE);

    shape_list_cleanup(list);
    return 0;
}

static char * test_length() {

    Texture t = texture_flat(0.5, colour(0, 0, 0));
    ShapeList empty = shape_list_empty();
    mu_assert("Error: ShapeList should be empty", shape_list_is_empty(empty) == true);
    ShapeList shapes = shape_list_add(
        empty, 4,
        sphere_create(vector3d(1.0, 2.0, 3.0), 1.0, t),
        sphere_create(vector3d(1.0, 2.0, 3.0), 1.0, t),
        sphere_create(vector3d(1.0, 2.0, 3.0), 1.0, t),
        sphere_create(vector3d(1.0, 2.0, 3.0), 1.0, t)
    );

    int len = shape_list_length(shapes);

    mu_assert("Error: ShapeList is not empty", shape_list_is_empty(shapes) == false);
    mu_assert("Error: ShapeList length not correct", len == 4);

    shape_list_cleanup(shapes);
    return 0;
}

char * test_shape_list() {
    mu_run_test(test_creation);
    mu_run_test(test_length);
    return 0;
}


