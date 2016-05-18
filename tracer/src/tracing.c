#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "tracing.h"

#include "colours.h"
#include "scene.h"
#include "shapes.h"
#include "lights.h"
#include "textures.h"
#include "ray.h"
#include "vector.h"
#include "camera.h"
#include "config.h"

#include "constants.h"

#include "bclib/list.h"

/* Generate rays for each pixel in the canvas.
 * These get shot out into the scene to see what objects they hit
 */
void rays_calc(Scene *scene) {

    int x, y;
    Config *config = scene->config;
    Camera *camera = scene->camera;

    double fovRadians   = (M_PI / 180) * (camera->fov / 2);
    double heightWidthRatio = (double)config->height / config->width;
    double halfWidth    = tan(fovRadians);
    double halfHeight   = heightWidthRatio * halfWidth;
    double cameraWidth  = halfWidth * 2;
    double cameraHeight = halfHeight * 2;
    double pixelWidth   = cameraWidth / (config->width - 1);
    double pixelHeight  = cameraHeight / (config->height - 1);

    Vector3D eyeVector = vector3d_unit(
        vector3d_subtract(
             camera->looking_at, camera->position
        )
    );
    Vector3D vpRight = vector3d_unit(
        vector3d_cross(
             eyeVector, vector3d(0, 1.0, 0)
        )
    );
    Vector3D vpUp = vector3d_unit(
        vector3d_cross(
             vpRight, eyeVector
        )
    );

    Vector3D xcomp, ycomp;

    int depth = 0;
    Ray pxRay;
    Vector3D rayDirection;
    Colour pxColour;
    for (x = 0; x < config->width; x += 1) {
        for (y = 0; y < config->height; y += 1) {
            xcomp = vector3d_scale((x * pixelWidth) - halfWidth, vpRight);
            ycomp = vector3d_scale((y * pixelHeight) - halfHeight, vpUp);
            rayDirection = vector3d_unit(
                vector3d_add(
                    vector3d_add(
                        eyeVector, xcomp
                    ),
                    ycomp
                )
            );
            pxRay = ray(camera->position, rayDirection);
            pxColour = trace(pxRay, scene, depth);
            canvas_set(scene->canvas, x, y, pxColour);
        }
    }

}

/* Calculate if a ray intersects with any objects and if so, what
 * colour pixel it gets
 */
Colour trace(Ray trace_ray, Scene *scene, int depth) {

    if (depth > scene->config->reflection_depth) {
        return colour(0, 0, 0);
    }

    // find the distance to the object that the ray intersects with
    Intersection distObject = intersectedObject(trace_ray, scene->shapes, scene->config->max_distance);

    // if it doesn't intersect with an object then return the background
    // colour
    if (distObject.object == NULL) {
        return scene->config->background;
    }

    Vector3D intersectPoint = vector3d_add(
        trace_ray.origin,
        vector3d_scale(distObject.distance, trace_ray.direction)
    );

    return surface(trace_ray, scene, distObject.object, intersectPoint, depth);
}

/* given a ray, itterate through all the objects and see if it intersects
 * with any. return the distance to it, or NULL if there's no intersection
 */
Intersection intersectedObject(Ray trace_ray, List *shapes, double max_distance) {
    Intersection distObject;
    distObject.object = NULL;
    distObject.distance = max_distance;
    Shape *s = NULL;

    double d;
    LIST_FOREACH(shapes, first, next, el) {
        s = el->value;
        d = shape_intersect(s, trace_ray);
        if (d > LIMINALITY && d < distObject.distance) {
            distObject.object = s;
            distObject.distance = d;
        }
    }

    return distObject;
}

/* given a shape, and a ray that intersects with it, calculate the colour
 * of the pixel.
 * This needs to account for the lambert, ambient and reflection.
 */
Colour surface(Ray trace_ray, Scene *scene, Shape *object, Vector3D intersection, int depth) {
    Vector3D normal = shape_normal(object, intersection);
    List *lights = scene->lights;
    Light *light;
    double lambert_value;
    Colour lambert_light = colour(0, 0, 0);
    Colour ambient_light = colour(0, 0, 0);
    Colour reflection_light = colour(0, 0, 0);

    LIST_FOREACH(lights, first, next, el) {
        light = el->value;
        switch(light->type) {
            case POINT:
                if (light_is_visible(
                        intersection,
                        light,
                        scene->shapes,
                        scene->config->max_distance
                    )) {
                    lambert_value = calc_lambert_value(intersection, normal, light);
                    colour_add(
                        lambert_light,
                        colour_scale(
                            light->colour,
                            lambert_value * object->texture.lambert
                        )
                    );
                }
                break;
            case AMBIENT:
                ambient_light = colour_add(ambient_light, colour_scale(light->colour, light->intensity));
                break;
        }
    }

    if (object->texture.specular > 0) {
        Vector3D reflection_direction = vector3d_reflection(normal, trace_ray.direction);
        Ray reflection_ray = ray(intersection, reflection_direction);
        Colour reflection_colour = trace(reflection_ray, scene, depth+1);
        reflection_light = colour_add(reflection_light, colour_scale(reflection_colour, object->texture.specular));
    }

    Colour light_value = colour_add(colour_ceil(lambert_light), ambient_light);
    return colour_ceil(
        colour_add(
            colour_ceil(
                colour_filter(
                    texture_get_colour(object->texture), light_value
                )
            ),
            reflection_light
        )
    );
}

/* Given a point on the surface of a shape and a light, see if the light
 * is visible. If there is another shape inbetween the point of intersection then it's not visible.
 * Ambient lights are never visible here.
 */
bool light_is_visible(Vector3D intersection, Light *light, List *shapes, double max_distance) {

    Intersection distObject;

    switch(light->type) {
        case AMBIENT:
            return false;
            break;
        case POINT:
            distObject = intersectedObject(
                ray_from_to(intersection, light->point.position),
                shapes,
                max_distance
            );
            return (distObject.object == NULL);
            break;
    }
}

double calc_lambert_value(Vector3D intersection, Vector3D normal, Light *light) {
    double lambertValue = vector3d_dot(
        vector3d_unit(
            vector3d_subtract(
                light->point.position, intersection
            )
        ),
        normal
    );
    return (lambertValue * light->intensity);
}



