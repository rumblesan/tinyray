#include <stdio.h>

#include "tests/min_unit.h"

#include "core/lights.h"
#include "core/collections/light_list.h"

static char * test_creation() {

    Light light = light_create(vector3d(1.0, 2.0, 3.0), 1.0);
    LightList list = light_list_add(light_list_create(), light);

    mu_assert("Error: LightList not created correctly", list->head.position.x == 1.0);

    light_list_cleanup(list);
    return 0;
}

static char * test_length() {
    LightList empty = light_list_create();
    mu_assert("Error: LightList should be empty", light_list_empty(empty) == true);
    LightList list1 = light_list_add(empty, light_create(vector3d(1.0, 2.0, 3.0), 1.0));
    LightList list2 = light_list_add(list1, light_create(vector3d(1.0, 2.0, 3.0), 1.0));
    LightList list3 = light_list_add(list2, light_create(vector3d(1.0, 2.0, 3.0), 1.0));
    LightList list4 = light_list_add(list3, light_create(vector3d(1.0, 2.0, 3.0), 1.0));

    int len = light_list_length(list4);

    mu_assert("Error: LightList is not empty", light_list_empty(list4) == false);
    mu_assert("Error: LightList length not correct", len == 4);

    light_list_cleanup(list4);
    return 0;
}

char * test_light_list() {
    mu_run_test(test_creation);
    mu_run_test(test_length);
    return 0;
}


