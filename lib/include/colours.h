#ifndef COLOURS_H
#define COLOURS_H

#include <stdint.h>

typedef double Component;

typedef struct Colour {

    Component red;
    Component green;
    Component blue;
    Component alpha;

} Colour;

Colour colour(Component red, Component green, Component blue);

Colour colour_add(Colour c1, Colour c2);

Colour colour_filter(Colour primary, Colour filter);

Colour colour_scale(Colour c, double scaler);

Colour colour_normalise(Colour c);

Colour colour_ceil(Colour c);

double colour_brightness(Colour c);

#endif
