#include <stdlib.h>

#include "langfuncs/tracescene.h"

#include "interpreter.h"
#include "interpreter_funcs.h"
#include "datavalue.h"
#include "bclib/list.h"
#include "bclib/bstrlib.h"

#include "scene.h"
#include "tracing.h"
#include "img_export.h"

#include "dbg.h"

void *tlist_to_clist(List *traylist) {
    List *clist = list_create();
    void *v;
    int len = list_count(traylist);
    for (int i = 0; i < len; i += 1) {
        v = list_get(traylist, i);
        list_push(clist, v);
    }
    return clist;
}

DataValue *config(Interpreter *interpreter, int arg_num) {
    double *width   = get_arg(interpreter);
    check(width, "config width arg error");
    double *height  = get_arg(interpreter);
    check(height, "config height arg error");
    double *maxdist = get_arg(interpreter);
    check(maxdist, "config max distance arg error");
    double *reflect = get_arg(interpreter);
    check(reflect, "config reflections arg error");
    Colour *colour  = get_arg(interpreter);
    check(colour, "config colour arg error");
    return datavalue_cdata(config_create(*width, *height, *maxdist, *reflect, *colour));
error:
    return NULL;
}

DataValue *camera(Interpreter *interpreter, int arg_num) {
    double   *fov  = get_arg(interpreter);
    check(fov, "camera fov arg error");
    Vector3D *pos  = get_arg(interpreter);
    check(pos, "camera position arg error");
    Vector3D *look = get_arg(interpreter);
    check(look, "camera look_at arg error");
    return datavalue_cdata(camera_create(*fov, *pos, *look));
error:
    return NULL;
}

DataValue *col(Interpreter *interpreter, int arg_num) {
    double *r = get_arg(interpreter);
    check(r, "col red arg error");
    double *g = get_arg(interpreter);
    check(g, "col green arg error");
    double *b = get_arg(interpreter);
    check(b, "col blue arg error");
    Colour *c = malloc(sizeof(Colour));
    check_mem(c);
    *c = colour(*r, *g, *b);
    return datavalue_cdata(c);
error:
    return NULL;
}

DataValue *vec(Interpreter *interpreter, int arg_num) {
    double   *x = get_arg(interpreter);
    check(x, "vec x arg error");
    double   *y = get_arg(interpreter);
    check(y, "vec y arg error");
    double   *z = get_arg(interpreter);
    check(z, "vec z arg error");
    Vector3D *v = malloc(sizeof(Vector3D));
    check_mem(v);
    *v = vector3d(*x, *y, *z);
    return datavalue_cdata(v);
error:
    return NULL;
}

DataValue *texture(Interpreter *interpreter, int arg_num) {
    double *lambert  = get_arg(interpreter);
    check(lambert, "texture lambert arg error");
    double *specular = get_arg(interpreter);
    check(specular, "texture specular arg error");
    Colour *col      = get_arg(interpreter);
    check(col, "texture col arg error");
    Texture *t = malloc(sizeof(Texture));
    check_mem(t);
    *t = texture_flat(*lambert, *specular, *col);
    return datavalue_cdata(t);
error:
    return NULL;
}

DataValue *pointlight(Interpreter *interpreter, int arg_num) {
    Vector3D *position  = get_arg(interpreter);
    check(position, "pointlight position arg error");
    double   *intensity = get_arg(interpreter);
    check(intensity, "pointlight intensity arg error");
    Colour   *colour    = get_arg(interpreter);
    check(colour, "pointlight colour arg error");
    return datavalue_cdata(point_light_create(*position, *intensity, *colour));
error:
    return NULL;
}

DataValue *ambientlight(Interpreter *interpreter, int arg_num) {
    double *intensity = get_arg(interpreter);
    check(intensity, "ambientlight intensity arg error");
    Colour *colour    = get_arg(interpreter);
    check(colour, "ambientlight colour arg error");
    return datavalue_cdata(ambient_light_create(*intensity, *colour));
error:
    return NULL;
}

DataValue *triangle(Interpreter *interpreter, int arg_num) {
    Vector3D *p1  = get_arg(interpreter);
    check(p1, "triangle p1 arg error");
    Vector3D *p2  = get_arg(interpreter);
    check(p2, "triangle p2 arg error");
    Vector3D *p3  = get_arg(interpreter);
    check(p3, "triangle p3 arg error");
    Texture  *txt = get_arg(interpreter);
    check(txt, "triangle texture arg error");
    return datavalue_cdata(shape_triangle(*p1, *p2, *p3, *txt));
error:
    return NULL;
}

DataValue *sphere(Interpreter *interpreter, int arg_num) {
    Vector3D *pos = get_arg(interpreter);
    check(pos, "sphere position arg error");
    double   *rad = get_arg(interpreter);
    check(rad, "sphere radius arg error");
    Texture  *txt = get_arg(interpreter);
    check(txt, "sphere texture arg error");
    return datavalue_cdata(shape_sphere(*pos, *rad, *txt));
error:
    return NULL;
}

DataValue *plane(Interpreter *interpreter, int arg_num) {
    Vector3D *pos = get_arg(interpreter);
    check(pos, "plane position arg error");
    Vector3D *nor = get_arg(interpreter);
    check(nor, "plane normal arg error");
    Texture  *txt = get_arg(interpreter);
    check(txt, "plane texture arg error");
    return datavalue_cdata(shape_plane(*pos, *nor, *txt));
error:
    return NULL;
}

DataValue *rayscene(Interpreter *interpreter, int arg_num) {
    Camera *camera = get_arg(interpreter);
    check(camera, "scene camera arg error");
    Config *config = get_arg(interpreter);
    check(config, "scene config arg error");
    List   *lights = tlist_to_clist(get_arg(interpreter));
    check(lights, "scene lights arg error");
    List   *shapes = tlist_to_clist(get_arg(interpreter));
    check(shapes, "scene shapes arg error");
    return datavalue_cdata(scene_create(camera, config, lights, shapes));
error:
    return NULL;
}

DataValue *trace_scene(Interpreter *interpreter, int arg_num) {
    Scene *scene = get_arg(interpreter);
    check(scene, "trace scene arg error");
    bstring name = get_arg(interpreter);
    check(scene, "output name arg error");
    rays_calc(scene);
    render_png(scene, name);
    scene_cleanup(scene);
    printf("output scene to file: %s\n", bdata(name));
    return datavalue_cdata(datavalue_nothing());
error:
    return NULL;
}

