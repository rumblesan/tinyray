
#include "core/colours.h"

Colour colour(Component red, Component green, Component blue, Component alpha) {

    return (red & (green << 8) & (blue << 16) & (alpha << 24));

}

