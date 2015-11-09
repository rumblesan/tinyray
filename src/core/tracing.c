#include <stdlib.h>
#include <math.h>

#include "core/tracing.h"

#include "core/colours.h"
#include "core/scene.h"
#include "core/shapes.h"
#include "core/ray.h"
#include "core/vector.h"
#include "core/camera.h"
#include "core/config.h"


void rays_calc(Scene scene) {

    int x, y;
    Config config = scene->config;
    Camera camera = scene->camera;

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

Colour trace(Ray ray, Scene scene, int depth) {

    Intersection distObject = intersectedObject(ray, scene->shapes, scene->config->max_distance);

    if (distObject.object == NULL) {
        return scene->config->background;
    }

    Vector3D intersectPoint = vector3d_add(
        ray.origin,
        vector3d_scale(distObject.distance, ray.direction)
    );

    return surface(ray, scene, distObject.object, intersectPoint, depth);
}

Intersection intersectedObject(Ray ray, ShapeList shapes, double max_distance) {
    Intersection distObject;
    distObject.object = NULL;
    distObject.distance = max_distance;

    ShapeList s = shapes;

    double d;
    while (!shape_list_is_empty(s)) {
        d = shape_intersect(shape_list_head(s), ray);
        if (d > 0 && d < distObject.distance) {
            distObject.object = shape_list_head(s);
            distObject.distance = d;
        }
        s = shape_list_tail(s);
    }

    return distObject;
}

Colour surface(Ray ray, Scene scene, Shape object, Vector3D intersection, int depth) {
    Vector3D normal = shape_normal(object, intersection);
    LightList lights = scene->lights;
    Light light;
    double contribution;
    double lambertAmount = 0;

    while(!light_list_is_empty(lights)) {
        light = light_list_head(lights);
        switch(light.type) {
            case POINT:
                if (light_is_visible(intersection, scene, light)) {
                    contribution = vector3d_dot(
                        vector3d_unit(
                            vector3d_subtract(
                                light.point.position, intersection
                            )
                        ),
                        normal
                    );
                    if (contribution > 0) {
                        lambertAmount += (contribution * light.intensity);
                    }
                }
                break;
            case AMBIENT:
                lambertAmount += light.intensity;
                break;
        }
        lights = light_list_tail(lights);
    }

    return colour_mult(object->colour, fmin(1, lambertAmount));
}

bool light_is_visible(Vector3D intersection, Scene scene, Light light) {

    Intersection distObject;

    switch(light.type) {
        case AMBIENT:
            return false;
            break;
        case POINT:
            distObject = intersectedObject(
                ray(intersection, vector3d_unit(
                    vector3d_subtract(intersection, light.point.position)
                )),
                scene->shapes,
                scene->config->max_distance
            );
            return (distObject.distance > -0.005);
            break;
    }
}

