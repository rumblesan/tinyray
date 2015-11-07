
#include "core/colours.h"

Colour colour(Component red, Component green, Component blue, Component alpha) {

    Colour c;

    c.red   = red;
    c.green = green;
    c.blue  = blue;
    c.alpha = alpha;

    return c;
}

