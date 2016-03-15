#ifndef LANGUAGE_STDLIB_SCENE_H
#define LANGUAGE_STDLIB_SCENE_H

#include "language/interpreter.h"
#include "bclib/list.h"

DataValue *config(List *args);

DataValue *camera(List *args);

DataValue *col(List *args);

DataValue *vec(List *args);

DataValue *texture(List *args);

DataValue *pointlight(List *args);

DataValue *ambientlight(List *args);

DataValue *triangle(List *args);

DataValue *sphere(List *args);

DataValue *plane(List *args);

DataValue *rayscene(List *args);

#endif
