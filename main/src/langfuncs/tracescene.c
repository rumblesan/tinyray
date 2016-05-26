#include <stdlib.h>

#include "langfuncs/tracescene.h"

#include "interpreter.h"
#include "interpreter_funcs.h"
#include "object.h"
#include "bclib/list.h"
#include "bclib/bstrlib.h"

#include "scene.h"
#include "tracing.h"
#include "img_export.h"

#include "dbg.h"

void *tlist_to_clist(List *traylist) {
    List *clist = list_create();
    Object *obj;
    int len = list_count(traylist);
    for (int i = 0; i < len; i += 1) {
        obj = list_get(traylist, i);
        list_push(clist, obj->cdata);
    }
    return clist;
}

Object *config(Interpreter *interpreter, int arg_num) {
    Object *width   = get_obj(interpreter);
    check(width, "config width arg error");
    Object *height  = get_obj(interpreter);
    check(height, "config height arg error");
    Object *maxdist = get_obj(interpreter);
    check(maxdist, "config max distance arg error");
    Object *reflect = get_obj(interpreter);
    check(reflect, "config reflections arg error");
    Object *colour  = get_obj(interpreter);
    check(colour, "config colour arg error");
    return object_cdata(
        interpreter,
        config_create(
            width->number, height->number, maxdist->number,
            reflect->number, *(Colour*)(colour->cdata)
        )
    );
error:
    return NULL;
}

Object *camera(Interpreter *interpreter, int arg_num) {
    Object *fov  = get_obj(interpreter);
    check(fov, "camera fov arg error");
    Object *pos  = get_obj(interpreter);
    check(pos, "camera position arg error");
    Object *look = get_obj(interpreter);
    check(look, "camera look_at arg error");
    return object_cdata(
        interpreter,
        camera_create(fov->number, *(Vector3D*)pos->cdata, *(Vector3D*)look->cdata)
    );
error:
    return NULL;
}

Object *col(Interpreter *interpreter, int arg_num) {
    Object *r = get_obj(interpreter);
    check(r, "col red arg error");
    Object *g = get_obj(interpreter);
    check(g, "col green arg error");
    Object *b = get_obj(interpreter);
    check(b, "col blue arg error");
    Colour *c = malloc(sizeof(Colour));
    check_mem(c);
    *c = colour(r->number, g->number, b->number);
    return object_cdata(interpreter, c);
error:
    return NULL;
}

Object *vec(Interpreter *interpreter, int arg_num) {
    Object   *x = get_obj(interpreter);
    check(x, "vec x arg error");
    Object   *y = get_obj(interpreter);
    check(y, "vec y arg error");
    Object   *z = get_obj(interpreter);
    check(z, "vec z arg error");
    Vector3D *v = malloc(sizeof(Vector3D));
    check_mem(v);
    *v = vector3d(x->number, y->number, z->number);
    return object_cdata(interpreter, v);
error:
    return NULL;
}

Object *texture(Interpreter *interpreter, int arg_num) {
    Object *lambert  = get_obj(interpreter);
    check(lambert, "texture lambert arg error");
    Object *specular = get_obj(interpreter);
    check(specular, "texture specular arg error");
    Object *col      = get_obj(interpreter);
    check(col, "texture col arg error");
    Texture *t = malloc(sizeof(Texture));
    check_mem(t);
    *t = texture_flat(lambert->number, specular->number, *(Colour*)col->cdata);
    return object_cdata(interpreter, t);
error:
    return NULL;
}

Object *pointlight(Interpreter *interpreter, int arg_num) {
    Object *position  = get_obj(interpreter);
    check(position, "pointlight position arg error");
    Object *intensity = get_obj(interpreter);
    check(intensity, "pointlight intensity arg error");
    Object *colour    = get_obj(interpreter);
    check(colour, "pointlight colour arg error");
    return object_cdata(
        interpreter,
        point_light_create(
            *(Vector3D*)position->cdata, intensity->number, *(Colour*)colour->cdata
        )
    );
error:
    return NULL;
}

Object *ambientlight(Interpreter *interpreter, int arg_num) {
    Object *intensity = get_obj(interpreter);
    check(intensity, "ambientlight intensity arg error");
    Object *colour    = get_obj(interpreter);
    check(colour, "ambientlight colour arg error");
    return object_cdata(
        interpreter,
        ambient_light_create(intensity->number, *(Colour*)colour->cdata)
    );
error:
    return NULL;
}

Object *triangle(Interpreter *interpreter, int arg_num) {
    Object *p1  = get_obj(interpreter);
    check(p1, "triangle p1 arg error");
    Object *p2  = get_obj(interpreter);
    check(p2, "triangle p2 arg error");
    Object *p3  = get_obj(interpreter);
    check(p3, "triangle p3 arg error");
    Object *txt = get_obj(interpreter);
    check(txt, "triangle texture arg error");
    return object_cdata(
        interpreter,
        shape_triangle(
            *(Vector3D*)p1->cdata,
            *(Vector3D*)p2->cdata,
            *(Vector3D*)p3->cdata,
            *(Texture*)txt->cdata)
    );
error:
    return NULL;
}

Object *sphere(Interpreter *interpreter, int arg_num) {
    Object *pos = get_obj(interpreter);
    check(pos, "sphere position arg error");
    Object *rad = get_obj(interpreter);
    check(rad, "sphere radius arg error");
    Object *txt = get_obj(interpreter);
    check(txt, "sphere texture arg error");
    return object_cdata(
        interpreter,
        shape_sphere(
            *(Vector3D*)pos->cdata,
            rad->number,
            *(Texture*)txt->cdata
        )
    );
error:
    return NULL;
}

Object *plane(Interpreter *interpreter, int arg_num) {
    Object *pos = get_obj(interpreter);
    check(pos, "plane position arg error");
    Object *nor = get_obj(interpreter);
    check(nor, "plane normal arg error");
    Object *txt = get_obj(interpreter);
    check(txt, "plane texture arg error");
    return object_cdata(
        interpreter,
        shape_plane(
            *(Vector3D*)pos->cdata,
            *(Vector3D*)nor->cdata,
            *(Texture*)txt->cdata
        )
    );
error:
    return NULL;
}

Object *rayscene(Interpreter *interpreter, int arg_num) {
    Object *camera = get_obj(interpreter);
    check(camera, "scene camera arg error");
    Object *config = get_obj(interpreter);
    check(config, "scene config arg error");

    Object *lights = get_obj(interpreter);
    check(lights, "scene lights arg error");
    List *light_list = tlist_to_clist(lights->list);

    Object *shapes = get_obj(interpreter);
    check(shapes, "scene shapes arg error");
    List *shape_list = tlist_to_clist(shapes->list);
    return object_cdata(
        interpreter,
        scene_create(camera->cdata, config->cdata, light_list, shape_list)
    );
error:
    return NULL;
}

Object *trace_scene(Interpreter *interpreter, int arg_num) {
    Object *scene = get_obj(interpreter);
    check(scene, "trace scene arg error");
    Object *name = get_obj(interpreter);
    check(scene, "output name arg error");
    rays_calc(scene->cdata);
    render_png(scene->cdata, name->string);
    scene_cleanup(scene->cdata);
    printf("output scene to file: %s\n", bdata(name->string));
    return object_nothing(interpreter);
error:
    return NULL;
}

