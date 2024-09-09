#ifndef LIGHTING_HPP
#define LIGHTING_HPP

#include <stdint.h>

static const size_t SIZE_ONE_COLOR = 3;

class Lighting
{
    int x;
    int y;
    const uint8_t* color;
    uint8_t brightness;
public:
    Lighting (int x, int y, uint8_t brightness, const uint8_t* color):
              x (x), y (y), brightness (brightness), color (color) {}

    void set_volume (uint8_t new_brightness)
    {
        brightness = new_brightness;
    }
};

#endif // LIGHTING_HPP
