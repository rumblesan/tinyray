#ifndef LANGUAGE_STDLIB_SCENE_H
#define LANGUAGE_STDLIB_SCENE_H

#include "traylang/interpreter.h"
#include "traylang/object.h"
#include "bclib/list.h"

Object *config(Interpreter *interpreter, int arg_num);

Object *camera(Interpreter *interpreter, int arg_num);

Object *col(Interpreter *interpreter, int arg_num);

Object *vec(Interpreter *interpreter, int arg_num);

Object *texture(Interpreter *interpreter, int arg_num);

Object *pointlight(Interpreter *interpreter, int arg_num);

Object *ambientlight(Interpreter *interpreter, int arg_num);

Object *triangle(Interpreter *interpreter, int arg_num);

Object *sphere(Interpreter *interpreter, int arg_num);

Object *plane(Interpreter *interpreter, int arg_num);

Object *rayscene(Interpreter *interpreter, int arg_num);

Object *trace_scene(Interpreter *interpreter, int arg_num);

#endif
