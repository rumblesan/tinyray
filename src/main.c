#include <stdio.h>
#include <stdlib.h>

#include "core/canvas.h"
#include "core/camera.h"
#include "core/config.h"
#include "core/lights.h"
#include "core/scene.h"
#include "core/shapes.h"
#include "core/textures.h"
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
        640, 480,
        10000,
        colour(0, 0, 0)
    );

    Camera camera = camera_create(
        45,
        vector3d(-5.0, 5.0, 0.0),
        vector3d(0.0, 0.0, 0.0)
    );
    LightList lights = light_list_create(
        2,
        point_light_create(
            vector3d(0.0, 2.1, 0), 0.4, colour(255, 255, 255)
        ),
        ambient_light_create(
            0.3, colour(255, 255, 255)
        )
    );
    Shape sphereO = sphere_create(
        vector3d(0.0, 0.0, 0.0),
        0.3,
        texture_flat(1, colour(255, 0, 255))
    );
    Shape sphere1 = sphere_create(
        vector3d(0.0, 1.0, 0.0),
        1,
        texture_flat(1, colour(0, 0, 255))
    );
    Shape plane = plane_create(
        vector3d(0.0, -1.0, 0.0),
        vector3d(0.0, 1.0, 0.0),
        texture_flat(1, colour(100, 100, 100))
    );

    ShapeList shapes = shape_list_create(
        3, sphereO, sphere1, plane
    );

    Scene scene = scene_create(
        camera,
        config,
        lights,
        shapes
    );

    rays_calc(scene);

    render_png(scene, "output.png");

    return 0;
}

