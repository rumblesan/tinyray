#ifndef CONFIG_H
#define CONFIG_H

typedef struct config *Config;
typedef struct config {

    int width;
    int height;

    int background;

} Config_Data;

Config config_create(int width, int height, int background);

void config_cleanup(Config config);

#endif

