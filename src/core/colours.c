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

Colour colour_add(Colour c1, Colour c2) {
    Colour newC;

    newC.red   = c1.red   + c2.red;
    newC.green = c1.green + c2.green;
    newC.blue  = c1.blue  + c2.blue;
    newC.alpha = 255;

    return newC;
}

Colour colour_filter(Colour primary, Colour filter) {
    Colour newC;

    newC.red   = primary.red * (filter.red / 255);
    newC.green = primary.green * (filter.green / 255);
    newC.blue  = primary.blue * (filter.blue / 255);
    newC.alpha = 255;

    return newC;
}

Colour colour_scale(Colour c, double scaler) {
    Colour newC;

    newC.red   = c.red * scaler;
    newC.green = c.green * scaler;
    newC.blue  = c.blue * scaler;
    newC.alpha = 255;

    return newC;
}

Colour colour_normalise(Colour c) {
    Colour newC;

    Component maxC = fmax(c.red, fmax(c.green, c.blue));

    newC.red   = (c.red   / maxC) * 255;
    newC.blue  = (c.blue  / maxC) * 255;
    newC.green = (c.green / maxC) * 255;
    newC.alpha = 255;

    return newC;
}

Colour colour_ceil(Colour c) {
    Colour newC;

    newC.red   = fmin(c.red, 255);
    newC.blue  = fmin(c.blue, 255);
    newC.green = fmin(c.green, 255);
    newC.alpha = 255;

    return newC;
}

double colour_brightness(Colour c) {

    return sqrt(
        pow(c.red, 2) + pow(c.green, 2) + pow(c.blue, 2)
    ) / (255 * sqrt(3));

}

