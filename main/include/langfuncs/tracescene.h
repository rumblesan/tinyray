#ifndef LANGUAGE_STDLIB_SCENE_H
#define LANGUAGE_STDLIB_SCENE_H

#include "interpreter.h"
#include "datavalue.h"
#include "bclib/list.h"

DataValue *config(Interpreter *interpreter, int arg_num);

DataValue *camera(Interpreter *interpreter, int arg_num);

DataValue *col(Interpreter *interpreter, int arg_num);

DataValue *vec(Interpreter *interpreter, int arg_num);

DataValue *texture(Interpreter *interpreter, int arg_num);

DataValue *pointlight(Interpreter *interpreter, int arg_num);

DataValue *ambientlight(Interpreter *interpreter, int arg_num);

DataValue *triangle(Interpreter *interpreter, int arg_num);

DataValue *sphere(Interpreter *interpreter, int arg_num);

DataValue *plane(Interpreter *interpreter, int arg_num);

DataValue *rayscene(Interpreter *interpreter, int arg_num);

DataValue *trace_scene(Interpreter *interpreter, int arg_num);

#endif
