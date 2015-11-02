#include <stdlib.h>
#include <math.h>

#include "core/config.h"

Config config_create(int width, int height, Colour background) {

    Config config = (Config) malloc(sizeof(ConfigData));

    config->width = width;
    config->height = height;

    config->background = background;

    return config;
}

void config_cleanup(Config config) {
    free(config);
}

