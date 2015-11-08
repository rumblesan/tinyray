#include <stdio.h>
#include <stdlib.h>

#include "core/canvas.h"
#include "core/camera.h"
#include "core/config.h"
#include "core/lights.h"
#include "core/scene.h"
#include "core/shapes.h"
#include "core/collections/light_list.h"
#include "core/collections/shape_list.h"

#include "core/tracing.h"

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
            colour = data[x][y];
            image[4 * width * y + 4 * x + 0] = colour.red;
            image[4 * width * y + 4 * x + 1] = colour.green;
            image[4 * width * y + 4 * x + 2] = colour.blue;
            image[4 * width * y + 4 * x + 3] = colour.alpha;
        }
    }

    err = lodepng_encode32_file(output_file, image, width, height);

    if (err) {
        printf("error %u: %s\n", err, lodepng_error_text(err));
    }
}

int main(int argc, char *argv[]) {

    Config config = config_create(
        640, 480,
        colour(0, 0, 0)
    );

    Canvas canvas = canvas_create(config->width, config->height);
    Camera camera = camera_create(
        45,
        -4.0, 0.0, 0.0,
        0.0, 0.0, 0.0
    );
    LightList lights = light_list_add(
        light_list_create(),
        light_create(-4.0, 0.0, 3.0, 1.0)
    );
    ShapeList shapes = shape_list_add(
        shape_list_create(),
        sphere_create(
            9.0, 0.0, 0.0,
            1.0,
            colour(200, 50, 100)
        )
    );

    Scene scene = scene_create(
        canvas,
        camera,
        config,
        lights,
        shapes
    );

    rays_calc(scene);

    render_png(scene, "output.png");

    return 0;
}

