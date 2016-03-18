#include <stdio.h>
#include <stdlib.h>

#include "img_export.h"

#include "dbg.h"

#include "scene.h"
#include "colours.h"
#include "bclib/bstrlib.h"
#include "libs/lodepng.h"

void render_png(Scene *scene, bstring output_file)
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

    err = lodepng_encode32_file(bdata(output_file), image, width, height);

    if (err) {
        printf("error %u: %s\n", err, lodepng_error_text(err));
    }
}

