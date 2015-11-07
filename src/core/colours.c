
#include "core/colours.h"

Colour colour(Component red, Component green, Component blue, Component alpha) {

    return ((red << 24) & (green << 16) & (blue << 8) & alpha);

}

