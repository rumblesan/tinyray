#include <stdlib.h>
#include <stdio.h>

#include "core/lights.h"
#include "core/light_list.h"

LightList light_list_create() {

    LightList list = (LightList) malloc(sizeof(LightListEl));

    list->head = NULL;
    list->tail = NULL;

    return list;
}

void light_list_cleanup(LightList list) {
    if (list->tail != NULL) {
        light_list_cleanup(list->tail);
    }
    if (list->head != NULL) {
        light_cleanup(list->head);
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

int light_list_length(LightList list) {
    LightList next;
    if (light_list_head(list) == NULL) {
        return 0;
    }
    int i = 0;
    next = light_list_tail(list);
    while(next != NULL) {
        i += 1;
        next = light_list_tail(next);
    }
    return i;
}

