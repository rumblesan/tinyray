#ifndef CONFIG_H
#define CONFIG_H

#include "core/colours.h"

typedef struct config *Config;
typedef struct config {

    int width;
    int height;

    double max_distance;

    Colour background;

} ConfigData;

Config config_create(
    int width,
    int height,
    double max_distance,
    Colour background
);

void config_cleanup(Config config);

#endif

