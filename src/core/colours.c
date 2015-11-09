#include <math.h>

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

    newC.red   = fmin(255, c.red * scaler);
    newC.green = fmin(255, c.green * scaler);
    newC.blue  = fmin(255, c.blue * scaler);
    newC.alpha = c.alpha;

    return newC;
}

