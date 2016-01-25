#ifndef TEXTURE_H
#define TEXTURE_H

#include "colours.h"

typedef enum {FLAT} TextureType;

typedef struct FlatTexture {

    Colour colour;

} FlatTexture;

typedef struct Texture {

    TextureType type;

    double lambert;

    double specular;

    union {
        FlatTexture flat;
    };

} Texture;

Texture texture_flat(double lambert, double specular, Colour colour);

Colour texture_get_colour(Texture texture);

#endif
