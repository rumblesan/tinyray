#include <stdlib.h>

#include "config.h"

#include "colours.h"

Config *config_create(
    int width,
    int height,
    double max_distance,
    int reflection_depth,
    Colour background
) {

    Config *config = malloc(sizeof(Config));

    config->width = width;
    config->height = height;

    config->max_distance = max_distance;
    config->reflection_depth = reflection_depth;

    config->background = background;

    return config;
}

void config_cleanup(Config *config) {
    free(config);
}

