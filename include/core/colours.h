#ifndef COLOURS_H
#define COLOURS_H

#include <stdint.h>

typedef uint8_t Component;

typedef struct colour_data {

    Component red;
    Component green;
    Component blue;
    Component alpha;

} Colour;

Colour colour(Component red, Component green, Component blue, Component alpha);

Colour colour_mult(Colour c, double scaler);

#endif
