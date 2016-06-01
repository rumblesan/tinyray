#include <stdlib.h>

#include "langfuncs/tracescene.h"

#include "traylang/traylang.h"
#include "traylang/traylang_ffi.h"

#include "bclib/list.h"
#include "bclib/bstrlib.h"

#include "scene.h"
#include "tracing.h"
#include "img_export.h"

#include "dbg.h"

void *tlist_to_clist(List *traylist) {
    List *clist = list_create();
    TrayObject *obj;
    int len = list_count(traylist);
    for (int i = 0; i < len; i += 1) {
        obj = list_get(traylist, i);
        list_push(clist, obj->cdata);
    }
    return clist;
}

TrayObject *config(TrayLangState *state, int arg_num) {
    TrayObject *width   = traylang_get_obj(state);
    check(width, "config width arg error");
    TrayObject *height  = traylang_get_obj(state);
    check(height, "config height arg error");
    TrayObject *maxdist = traylang_get_obj(state);
    check(maxdist, "config max distance arg error");
    TrayObject *reflect = traylang_get_obj(state);
    check(reflect, "config reflections arg error");
    TrayObject *colour  = traylang_get_obj(state);
    check(colour, "config colour arg error");
    return traylang_new_cdata(
        state,
        config_create(
            width->number, height->number, maxdist->number,
            reflect->number, *(Colour*)(colour->cdata)
        )
    );
error:
    return NULL;
}

TrayObject *camera(TrayLangState *state, int arg_num) {
    TrayObject *fov  = traylang_get_obj(state);
    check(fov, "camera fov arg error");
    TrayObject *pos  = traylang_get_obj(state);
    check(pos, "camera position arg error");
    TrayObject *look = traylang_get_obj(state);
    check(look, "camera look_at arg error");
    return traylang_new_cdata(
        state,
        camera_create(fov->number, *(Vector3D*)pos->cdata, *(Vector3D*)look->cdata)
    );
error:
    return NULL;
}

TrayObject *col(TrayLangState *state, int arg_num) {
    TrayObject *r = traylang_get_obj(state);
    check(r, "col red arg error");
    TrayObject *g = traylang_get_obj(state);
    check(g, "col green arg error");
    TrayObject *b = traylang_get_obj(state);
    check(b, "col blue arg error");
    Colour *c = malloc(sizeof(Colour));
    check_mem(c);
    *c = colour(r->number, g->number, b->number);
    return traylang_new_cdata(state, c);
error:
    return NULL;
}

TrayObject *vec(TrayLangState *state, int arg_num) {
    TrayObject   *x = traylang_get_obj(state);
    check(x, "vec x arg error");
    TrayObject   *y = traylang_get_obj(state);
    check(y, "vec y arg error");
    TrayObject   *z = traylang_get_obj(state);
    check(z, "vec z arg error");
    Vector3D *v = malloc(sizeof(Vector3D));
    check_mem(v);
    *v = vector3d(x->number, y->number, z->number);
    return traylang_new_cdata(state, v);
error:
    return NULL;
}

TrayObject *texture(TrayLangState *state, int arg_num) {
    TrayObject *lambert  = traylang_get_obj(state);
    check(lambert, "texture lambert arg error");
    TrayObject *specular = traylang_get_obj(state);
    check(specular, "texture specular arg error");
    TrayObject *col      = traylang_get_obj(state);
    check(col, "texture col arg error");
    Texture *t = malloc(sizeof(Texture));
    check_mem(t);
    *t = texture_flat(lambert->number, specular->number, *(Colour*)col->cdata);
    return traylang_new_cdata(state, t);
error:
    return NULL;
}

TrayObject *pointlight(TrayLangState *state, int arg_num) {
    TrayObject *position  = traylang_get_obj(state);
    check(position, "pointlight position arg error");
    TrayObject *intensity = traylang_get_obj(state);
    check(intensity, "pointlight intensity arg error");
    TrayObject *colour    = traylang_get_obj(state);
    check(colour, "pointlight colour arg error");
    return traylang_new_cdata(
        state,
        point_light_create(
            *(Vector3D*)position->cdata, intensity->number, *(Colour*)colour->cdata
        )
    );
error:
    return NULL;
}

TrayObject *ambientlight(TrayLangState *state, int arg_num) {
    TrayObject *intensity = traylang_get_obj(state);
    check(intensity, "ambientlight intensity arg error");
    TrayObject *colour    = traylang_get_obj(state);
    check(colour, "ambientlight colour arg error");
    return traylang_new_cdata(
        state,
        ambient_light_create(intensity->number, *(Colour*)colour->cdata)
    );
error:
    return NULL;
}

TrayObject *triangle(TrayLangState *state, int arg_num) {
    TrayObject *p1  = traylang_get_obj(state);
    check(p1, "triangle p1 arg error");
    TrayObject *p2  = traylang_get_obj(state);
    check(p2, "triangle p2 arg error");
    TrayObject *p3  = traylang_get_obj(state);
    check(p3, "triangle p3 arg error");
    TrayObject *txt = traylang_get_obj(state);
    check(txt, "triangle texture arg error");
    return traylang_new_cdata(
        state,
        shape_triangle(
            *(Vector3D*)p1->cdata,
            *(Vector3D*)p2->cdata,
            *(Vector3D*)p3->cdata,
            *(Texture*)txt->cdata)
    );
error:
    return NULL;
}

TrayObject *sphere(TrayLangState *state, int arg_num) {
    TrayObject *pos = traylang_get_obj(state);
    check(pos, "sphere position arg error");
    TrayObject *rad = traylang_get_obj(state);
    check(rad, "sphere radius arg error");
    TrayObject *txt = traylang_get_obj(state);
    check(txt, "sphere texture arg error");
    return traylang_new_cdata(
        state,
        shape_sphere(
            *(Vector3D*)pos->cdata,
            rad->number,
            *(Texture*)txt->cdata
        )
    );
error:
    return NULL;
}

TrayObject *plane(TrayLangState *state, int arg_num) {
    TrayObject *pos = traylang_get_obj(state);
    check(pos, "plane position arg error");
    TrayObject *nor = traylang_get_obj(state);
    check(nor, "plane normal arg error");
    TrayObject *txt = traylang_get_obj(state);
    check(txt, "plane texture arg error");
    return traylang_new_cdata(
        state,
        shape_plane(
            *(Vector3D*)pos->cdata,
            *(Vector3D*)nor->cdata,
            *(Texture*)txt->cdata
        )
    );
error:
    return NULL;
}

TrayObject *rayscene(TrayLangState *state, int arg_num) {
    TrayObject *camera = traylang_get_obj(state);
    check(camera, "scene camera arg error");
    TrayObject *config = traylang_get_obj(state);
    check(config, "scene config arg error");

    TrayObject *lights = traylang_get_obj(state);
    check(lights, "scene lights arg error");
    List *light_list = tlist_to_clist(lights->list);

    TrayObject *shapes = traylang_get_obj(state);
    check(shapes, "scene shapes arg error");
    List *shape_list = tlist_to_clist(shapes->list);
    return traylang_new_cdata(
        state,
        scene_create(camera->cdata, config->cdata, light_list, shape_list)
    );
error:
    return NULL;
}

TrayObject *trace_scene(TrayLangState *state, int arg_num) {
    TrayObject *scene = traylang_get_obj(state);
    check(scene, "trace scene arg error");
    TrayObject *name = traylang_get_obj(state);
    check(scene, "output name arg error");
    rays_calc(scene->cdata);
    render_png(scene->cdata, name->string);
    scene_cleanup(scene->cdata);
    printf("output scene to file: %s\n", bdata(name->string));
    return traylang_new_nothing(state);
error:
    return NULL;
}

