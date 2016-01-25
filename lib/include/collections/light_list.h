#ifndef LIGHT_LIST_H
#define LIGHT_LIST_H

#include <stdbool.h>

#include "lights.h"

struct LightList;

typedef struct LightList {

    Light head;

    struct LightList *tail;

} LightList;

LightList *light_list_element();

LightList *light_list_empty();

LightList *light_list_create(int count, ...);

void light_list_cleanup(LightList *list);

LightList *light_list_add(LightList *list, int count, ...);

Light light_list_head(LightList *list);

LightList *light_list_tail(LightList *list);

bool light_list_is_empty(LightList *list);

int light_list_length(LightList *list);

#endif
