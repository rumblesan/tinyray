#include <stdlib.h>
#include <stdbool.h>

#include "core/collections/light_list.h"

#include "core/lights.h"

LightList light_list_create() {

    LightList list = (LightList) malloc(sizeof(LightListEl));

    list->tail = NULL;

    return list;
}

void light_list_cleanup(LightList list) {
    if (list->tail != NULL) {
        light_list_cleanup(list->tail);
    }
    free(list);
}

LightList light_list_add(LightList list, Light light) {

    LightList new_head = light_list_create();

    new_head->head = light;
    new_head->tail = list;

    return new_head;
}

Light light_list_head(LightList list) {
    return list->head;
}

LightList light_list_tail(LightList list) {
    return list->tail;
}

bool light_list_empty(LightList list) {
    if (list->tail == NULL) {
        return true;
    } else {
        return false;
    }
}

int light_list_length(LightList list) {
    LightList l = list;
    int i = 0;
    while(!light_list_empty(l)) {
        i += 1;
        l = light_list_tail(l);
    }
    return i;
}

