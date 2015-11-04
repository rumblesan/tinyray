#ifndef LIGHT_LIST_H
#define LIGHT_LIST_H

#include "core/lights.h"

typedef struct light_list_el *LightList;
typedef struct light_list_el {

    Light head;

    LightList tail;

} LightListEl;

LightList light_list_create();

void light_list_cleanup(LightList list);

LightList light_list_add(LightList list, Light light);

Light light_list_head(LightList list); 

LightList light_list_tail(LightList list); 

int light_list_length(LightList list); 

#endif
