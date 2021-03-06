#ifndef CONFIG_H
#define CONFIG_H

#include "colours.h"

typedef struct Config {

    int width;
    int height;

    double max_distance;

    int reflection_depth;

    Colour background;

} Config;

Config *config_create(
    int width,
    int height,
    double max_distance,
    int reflection_depth,
    Colour background
);

void config_cleanup(Config *config);

#endif

