#ifndef COLOURS_H
#define COLOURS_H

#include <stdint.h>

typedef uint32_t Colour;
typedef uint8_t Component;

Colour colour(Component red, Component green, Component blue, Component alpha);

#endif
