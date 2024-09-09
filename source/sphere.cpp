#include "../include/sphere.hpp"
#include "../include/lighting.hpp"
#include "../include/drawing.hpp"

#include <stdint.h>
#include <string.h>

const size_t N_BYTES_FOR_PIXEL = 4;

uint8_t* get_sphere_pixels (Sphere sphere, Lighting lighting, GraphicSystem graphic_system)
{
    size_t x_window_size = graphic_system.get_x_size ();
    size_t y_window_size = graphic_system.get_y_size ();
    int green = 0xFF00FF00;
    uint8_t* pixels = (uint8_t*) calloc (x_window_size * y_window_size * N_BYTES_FOR_PIXEL, sizeof(uint8_t));

    for (size_t y_pixel_number; y_pixel_number < y_window_size; y_pixel_number++)
    {
        for (size_t x_pixel_number; x_pixel_number < x_window_size; x_pixel_number++)
        {
            if (SQUARE (sphere.get_x_center() + graphic_system.get_x_center () - x_pixel_number) +
                SQUARE (graphic_system.get_y_center () - sphere.get_y_center () - y_pixel_number) <=
                SQUARE (sphere.get_radius ()))
            {
                memcpy (pixels + 4 * x_pixel_number + y_pixel_number, &green, sizeof (int));
                continue;
            }
            int black = 0x00000000;
            memcpy (pixels + 4 * x_pixel_number + y_pixel_number, &green, sizeof (int));
        }
    }

    return pixels;
}
