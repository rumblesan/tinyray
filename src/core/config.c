#include <stdlib.h>

#include "core/config.h"

#include "core/colours.h"

Config config_create(
    int width,
    int height,
    double max_distance,
    Colour background
) {

    Config config = (Config) malloc(sizeof(ConfigData));

    config->width = width;
    config->height = height;

    config->max_distance = max_distance;

    config->background = background;

    return config;
}

void config_cleanup(Config config) {
    free(config);
}

