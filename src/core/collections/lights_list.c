#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#include "core/collections/light_list.h"

#include "core/lights.h"

LightList light_list_element() {

    LightList list = malloc(sizeof(LightListEl));

    list->tail = NULL;

    return list;
}

LightList light_list_empty() {
    return light_list_element();
}

LightList light_list_create(int count, ...) {

    va_list args;
    va_start (args, count);
    int i;

    Light add_light;
    LightList head;
    LightList tail = light_list_empty();

    for (i = 0; i < count; i++) {
        head = light_list_element();
        add_light = va_arg(args, Light);
        head->head = add_light;
        head->tail = tail;
        tail = head;
    }

    return head;
}

void light_list_cleanup(LightList list) {
    if (list->tail != NULL) {
        light_list_cleanup(list->tail);
    }
    free(list);
}

LightList light_list_add(LightList list, int count, ...) {

    va_list args;
    va_start (args, count);
    int i;

    Light add_light;
    LightList head;
    LightList tail = list;

    for (i = 0; i < count; i++) {
        head = light_list_element();
        add_light = va_arg(args, Light);
        head->head = add_light;
        head->tail = tail;
        tail = head;
    }

    return head;
}

Light light_list_head(LightList list) {
    return list->head;
}

LightList light_list_tail(LightList list) {
    return list->tail;
}

bool light_list_is_empty(LightList list) {
    if (list->tail == NULL) {
        return true;
    } else {
        return false;
    }
}

int light_list_length(LightList list) {
    LightList l = list;
    int i = 0;
    while(!light_list_is_empty(l)) {
        i += 1;
        l = light_list_tail(l);
    }
    return i;
}

