#include <stdio.h>

#include "tests/min_unit.h"

#include "core/lights.h"
#include "core/coordinates.h"
#include "core/light_list.h"

static char * test_creation() {

    Light light = light_create(1.0, 2.0, 3.0, 1.0);
    LightList list = light_list_add(light_list_create(), light);

    mu_assert("Error: LightList not created correctly", list->head->centre->x == 1.0);

    light_list_cleanup(list);
    return 0;
}

static char * test_length() {
    LightList empty = light_list_create();
    LightList list1 = light_list_add(empty, light_create(1.0, 2.0, 3.0, 1.0));
    LightList list2 = light_list_add(list1, light_create(1.0, 2.0, 3.0, 1.0));
    LightList list3 = light_list_add(list2, light_create(1.0, 2.0, 3.0, 1.0));
    LightList list4 = light_list_add(list3, light_create(1.0, 2.0, 3.0, 1.0));

    int len = light_list_length(list4);

    mu_assert("Error: LightList length not correct", len == 4);

    light_list_cleanup(list4);
    return 0;
}

char * test_light_list() {
    mu_run_test(test_creation);
    mu_run_test(test_length);
    return 0;
}


