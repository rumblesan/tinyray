#include "core/textures.h"

#include "core/colours.h"

Texture texture_flat(double lambert, Colour colour) {

    Texture texture;

    FlatTexture flat;
    flat.colour = colour;

    texture.type = FLAT;
    texture.flat = flat;
    texture.lambert = lambert;

    return texture;
}

Colour texture_get_colour(Texture texture) {
    switch (texture.type) {
        case FLAT:
            return texture.flat.colour;
            break;
    }
}
