#include <stdlib.h>

#include "language/interpreter.h"
#include "language/stdlib/tracescene.h"
#include "bclib/list.h"

#include "tracing.h"
#include "dbg.h"

DataValue *config(List *args) {
    double *width   = get_arg(args, 0);
    double *height  = get_arg(args, 1);
    double *maxdist = get_arg(args, 2);
    double *reflect = get_arg(args, 3);
    Colour *colour  = get_arg(args, 4);
    return datavalue_create(
        CONFIG,
        config_create(*width, *height, *maxdist, *reflect, *colour)
    );
}

DataValue *camera(List *args) {
    double   *fov  = get_arg(args, 0);
    Vector3D *pos  = get_arg(args, 1);
    Vector3D *look = get_arg(args, 2);
    return datavalue_create(
        CAMERA,
        camera_create(*fov, *pos, *look)
    );
}

DataValue *col(List *args) {
    double *r = get_arg(args, 0);
    double *g = get_arg(args, 1);
    double *b = get_arg(args, 2);
    Colour *c = malloc(sizeof(Colour));
    *c = colour(*r, *g, *b);
    return datavalue_create(COLOUR, c);
}

DataValue *vec(List *args) {
    double   *x = get_arg(args, 0);
    double   *y = get_arg(args, 1);
    double   *z = get_arg(args, 2);
    Vector3D *v = malloc(sizeof(Vector3D));
    *v = vector3d(*x, *y, *z);
    return datavalue_create(VECTOR, v);
}

DataValue *texture(List *args) {
    double *lambert  = get_arg(args, 0);
    double *specular = get_arg(args, 1);
    Colour *col      = get_arg(args, 2);
    Texture *t = malloc(sizeof(Texture));
    *t = texture_flat(*lambert, *specular, *col);
    return datavalue_create(TEXTURE, t);
}

DataValue *pointlight(List *args) {
    Vector3D *position  = get_arg(args, 0);
    double   *intensity = get_arg(args, 1);
    Colour   *colour    = get_arg(args, 2);
    return datavalue_create(
        LIGHT,
        point_light_create(*position, *intensity, *colour)
    );
}

DataValue *ambientlight(List *args) {
    double *intensity = get_arg(args, 1);
    Colour *colour    = get_arg(args, 2);
    return datavalue_create(
        LIGHT,
        ambient_light_create(*intensity, *colour)
    );
}

DataValue *triangle(List *args) {
    Vector3D *p1  = get_arg(args, 0);
    Vector3D *p2  = get_arg(args, 1);
    Vector3D *p3  = get_arg(args, 2);
    Texture  *txt = get_arg(args, 3);
    return datavalue_create(
        SHAPE,
        shape_triangle(*p1, *p2, *p3, *txt)
    );
}

DataValue *sphere(List *args) {
    Vector3D *pos = get_arg(args, 0);
    double   *rad = get_arg(args, 1);
    Texture  *txt = get_arg(args, 2);
    return datavalue_create(
        SHAPE,
        shape_sphere(*pos, *rad, *txt)
    );
}

DataValue *plane(List *args) {
    Vector3D *pos = get_arg(args, 0);
    Vector3D *nor = get_arg(args, 1);
    Texture  *txt = get_arg(args, 2);
    return datavalue_create(
        SHAPE,
        shape_plane(*pos, *nor, *txt)
    );
}

DataValue *rayscene(List *args) {
    debug("scene");
    Camera *camera = get_arg(args, 0);
    Config *config = get_arg(args, 1);
    List   *lights = get_arg(args, 2);
    List   *shapes = get_arg(args, 3);
    debug("creating scene");
    Scene *scene = scene_create(camera, config, lights, shapes);
    debug("created scene");
    return datavalue_create(SCENE, scene);
}

