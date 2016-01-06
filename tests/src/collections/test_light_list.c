#include <stdio.h>

#include "min_unit.h"

#include "lights.h"
#include "collections/light_list.h"
#include "colours.h"

static char * test_creation() {

    Colour c = colour(255, 255, 255);
    Light light = point_light_create(vector3d(1.0, 2.0, 3.0), 1.0, c);
    LightList list = light_list_create(1, light);

    mu_assert("Error: LightList not created correctly", list->head.point.position.x == 1.0);

    light_list_cleanup(list);
    return 0;
}

static char * test_length() {
    Colour c = colour(255, 255, 255);
    LightList empty = light_list_empty();
    mu_assert("Error: LightList should be empty", light_list_is_empty(empty) == true);
    LightList lights = light_list_add(
        empty, 4,
        point_light_create(vector3d(1.0, 2.0, 3.0), 1.0, c),
        point_light_create(vector3d(1.0, 2.0, 3.0), 1.0, c),
        point_light_create(vector3d(1.0, 2.0, 3.0), 1.0, c),
        point_light_create(vector3d(1.0, 2.0, 3.0), 1.0, c)
    );

    int len = light_list_length(lights);

    mu_assert("Error: LightList is not empty", light_list_is_empty(lights) == false);
    mu_assert("Error: LightList length not correct", len == 4);

    light_list_cleanup(lights);
    return 0;
}

char * test_light_list() {
    mu_run_test(test_creation);
    mu_run_test(test_length);
    return 0;
}


