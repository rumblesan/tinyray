#include "core/colours.h"

Colour colour(Component red, Component green, Component blue) {

    Colour c;

    c.red   = red;
    c.green = green;
    c.blue  = blue;
    c.alpha = 255;

    return c;
}

Colour colour_mult(Colour c, double scaler) {
    Colour newC;

    newC.red   = c.red * scaler;
    newC.green = c.green * scaler;
    newC.blue  = c.blue * scaler;
    newC.alpha = c.alpha;

    return newC;
}

