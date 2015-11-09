#ifndef TEXTURE_H
#define TEXTURE_H

#include "colours.h"

typedef enum {FLAT} TextureType;

typedef struct flat_texture {

    Colour colour;

} FlatTexture;

typedef struct texture {

    TextureType type;

    double lambert;

    union {
        FlatTexture flat;
    };

} Texture;

Texture texture_flat(double lambert, Colour colour);

Colour texture_get_colour(Texture texture);

#endif
