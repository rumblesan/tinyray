#include <stdio.h>
#include <stdlib.h>

#include "canvas.h"
#include "camera.h"
#include "config.h"
#include "lights.h"
#include "scene.h"
#include "shapes.h"
#include "textures.h"
#include "collections/light_list.h"
#include "collections/shape_list.h"

#include "tracing.h"

#include "libs/lodepng.h"

void render_png(Scene scene, char* output_file)
{
    int width  = scene->canvas->width;
    int height = scene->canvas->height;

    Colour **data = scene->canvas->data;

    Colour colour;

    unsigned err;

    unsigned char* image = malloc(width * height * 4);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Fix image being upside down
            // We trace from bottom left to top right
            // Logepng goes topleft to bottom right
            int yc = (height - 1) - y;
            colour = data[x][y];
            image[4 * width * yc + 4 * x + 0] = (uint8_t)colour.red;
            image[4 * width * yc + 4 * x + 1] = (uint8_t)colour.green;
            image[4 * width * yc + 4 * x + 2] = (uint8_t)colour.blue;
            image[4 * width * yc + 4 * x + 3] = (uint8_t)colour.alpha;
        }
    }

    err = lodepng_encode32_file(output_file, image, width, height);

    if (err) {
        printf("error %u: %s\n", err, lodepng_error_text(err));
    }
}

int main(int argc, char *argv[]) {

    Config config = config_create(
        1024, 768,
        10000,
        100,
        colour(210, 230, 255)
    );

    Camera camera = camera_create(
        45,
        vector3d(13, 7, 13),
        vector3d(0, 3, 0)
    );
    Light ambient = ambient_light_create(
        0.6, colour(255, 255, 255)
    );
    LightList lights = light_list_create(
        2,
        point_light_create(
            vector3d(0, 8, 7), 0.7, colour(255, 255, 255)
        ),
        ambient
    );

    Shape triangle = shape_triangle(
        vector3d(1.0,  2.0,  1.0),
        vector3d(1.0,  0.0,  6.0),
        vector3d(-3.0, 3.0,  6.0),
        texture_flat(1, 0.5, colour(255, 55, 55))
    );
    Shape sphere = shape_sphere(
        vector3d(0, 4, 0),
        3,
        texture_flat(0.2, 0.5, colour(155, 155, 155))
    );
    Shape small_sphere = shape_sphere(
        vector3d(0, 5, 3.7),
        0.3,
        texture_flat(1, 0.1, colour(0, 100, 150))
    );
    Shape plane = shape_plane(
        vector3d(0.0, 0.0, 0.0),
        vector3d(0.0, 1.0, 0.0),
        texture_flat(1, 0.2, colour(100, 100, 100))
    );
    ShapeList shapes = shape_list_create(
        4, sphere, small_sphere, plane, triangle
    );

    Scene scene = scene_create(
        camera,
        config,
        lights,
        shapes
    );

    rays_calc(scene);

    render_png(scene, "output.png");

    scene_cleanup(scene);

    return 0;
}

