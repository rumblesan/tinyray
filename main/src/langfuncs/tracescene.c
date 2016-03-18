#include <stdlib.h>

#include "langfuncs/tracescene.h"
#include "interpreter.h"
#include "bclib/list.h"

#include "tracing.h"
#include "dbg.h"

void *tlist_to_clist(List *traylist) {
    List *clist = list_create();
    int len = list_count(traylist);
    for (int i = 0; i < len; i += 1) {
        list_push(clist, get_arg(traylist, i));
    }
    return clist;
}

DataValue *config(List *args) {
    double *width   = get_arg(args, 0);
    check(width, "config width arg error");
    double *height  = get_arg(args, 1);
    check(height, "config height arg error");
    double *maxdist = get_arg(args, 2);
    check(maxdist, "config max distance arg error");
    double *reflect = get_arg(args, 3);
    check(reflect, "config reflections arg error");
    Colour *colour  = get_arg(args, 4);
    check(colour, "config colour arg error");
    return datavalue_create(
        USERDATA,
        config_create(*width, *height, *maxdist, *reflect, *colour)
    );
error:
    return NULL;
}

DataValue *camera(List *args) {
    double   *fov  = get_arg(args, 0);
    check(fov, "camera fov arg error");
    Vector3D *pos  = get_arg(args, 1);
    check(pos, "camera position arg error");
    Vector3D *look = get_arg(args, 2);
    check(look, "camera look_at arg error");
    return datavalue_create(
        USERDATA,
        camera_create(*fov, *pos, *look)
    );
error:
    return NULL;
}

DataValue *col(List *args) {
    double *r = get_arg(args, 0);
    check(r, "col red arg error");
    double *g = get_arg(args, 1);
    check(g, "col green arg error");
    double *b = get_arg(args, 2);
    check(b, "col blue arg error");
    Colour *c = malloc(sizeof(Colour));
    check_mem(c);
    *c = colour(*r, *g, *b);
    return datavalue_create(USERDATA, c);
error:
    return NULL;
}

DataValue *vec(List *args) {
    double   *x = get_arg(args, 0);
    check(x, "vec x arg error");
    double   *y = get_arg(args, 1);
    check(y, "vec y arg error");
    double   *z = get_arg(args, 2);
    check(z, "vec z arg error");
    Vector3D *v = malloc(sizeof(Vector3D));
    check_mem(v);
    *v = vector3d(*x, *y, *z);
    return datavalue_create(USERDATA, v);
error:
    return NULL;
}

DataValue *texture(List *args) {
    double *lambert  = get_arg(args, 0);
    check(lambert, "texture lambert arg error");
    double *specular = get_arg(args, 1);
    check(specular, "texture specular arg error");
    Colour *col      = get_arg(args, 2);
    check(col, "texture col arg error");
    Texture *t = malloc(sizeof(Texture));
    check_mem(t);
    *t = texture_flat(*lambert, *specular, *col);
    return datavalue_create(USERDATA, t);
error:
    return NULL;
}

DataValue *pointlight(List *args) {
    Vector3D *position  = get_arg(args, 0);
    check(position, "pointlight position arg error");
    double   *intensity = get_arg(args, 1);
    check(intensity, "pointlight intensity arg error");
    Colour   *colour    = get_arg(args, 2);
    check(colour, "pointlight colour arg error");
    return datavalue_create(
        USERDATA,
        point_light_create(*position, *intensity, *colour)
    );
error:
    return NULL;
}

DataValue *ambientlight(List *args) {
    double *intensity = get_arg(args, 0);
    check(intensity, "ambientlight intensity arg error");
    Colour *colour    = get_arg(args, 1);
    check(colour, "ambientlight colour arg error");
    return datavalue_create(
        USERDATA,
        ambient_light_create(*intensity, *colour)
    );
error:
    return NULL;
}

DataValue *triangle(List *args) {
    Vector3D *p1  = get_arg(args, 0);
    check(p1, "triangle p1 arg error");
    Vector3D *p2  = get_arg(args, 1);
    check(p2, "triangle p2 arg error");
    Vector3D *p3  = get_arg(args, 2);
    check(p3, "triangle p3 arg error");
    Texture  *txt = get_arg(args, 3);
    check(txt, "triangle texture arg error");
    return datavalue_create(
        USERDATA,
        shape_triangle(*p1, *p2, *p3, *txt)
    );
error:
    return NULL;
}

DataValue *sphere(List *args) {
    Vector3D *pos = get_arg(args, 0);
    check(pos, "sphere position arg error");
    double   *rad = get_arg(args, 1);
    check(rad, "sphere radius arg error");
    Texture  *txt = get_arg(args, 2);
    check(txt, "sphere texture arg error");
    return datavalue_create(
        USERDATA,
        shape_sphere(*pos, *rad, *txt)
    );
error:
    return NULL;
}

DataValue *plane(List *args) {
    Vector3D *pos = get_arg(args, 0);
    check(pos, "plane position arg error");
    Vector3D *nor = get_arg(args, 1);
    check(nor, "plane normal arg error");
    Texture  *txt = get_arg(args, 2);
    check(txt, "plane texture arg error");
    return datavalue_create(
        USERDATA,
        shape_plane(*pos, *nor, *txt)
    );
error:
    return NULL;
}

DataValue *rayscene(List *args) {
    Camera *camera = get_arg(args, 0);
    check(camera, "scene camera arg error");
    Config *config = get_arg(args, 1);
    check(config, "scene config arg error");
    List   *lights = tlist_to_clist(get_arg(args, 2));
    check(lights, "scene lights arg error");
    List   *shapes = tlist_to_clist(get_arg(args, 3));
    check(shapes, "scene shapes arg error");
    log_info("Creating scene");
    Scene *scene = scene_create(camera, config, lights, shapes);
    return datavalue_create(USERDATA, scene);
error:
    return NULL;
}

