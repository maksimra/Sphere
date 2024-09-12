#include "../include/sphere.hpp"
#include "../include/lighting.hpp"
#include "../include/drawing.hpp"
#include "../include/vector.hpp"

#include <stdint.h>
#include <string.h>
#include <math.h>

const size_t N_BYTES_FOR_PIXEL = 4;

int Sphere::get_x_center () const
{
    return x_center_;
}

int Sphere::get_y_center () const
{
    return y_center_;
}

size_t Sphere::get_radius () const
{
    return radius_;
}

void Sphere::set_radius (size_t new_radius)
{
    radius_ = new_radius;
}

int Sphere::get_rgba () const
{
    return color_;
}

uint8_t* Sphere::get_sphere_pixels (const Lighting& lighting, const GraphicSystem& graphic_system, double ambient_coeff)
{
    int pixel_color = 0;

    uint8_t* pixels = (uint8_t*) calloc (graphic_system.get_x_size () * graphic_system.get_y_size () * N_BYTES_FOR_PIXEL, sizeof(uint8_t));

    for (size_t y_pixel_number = 0; y_pixel_number < graphic_system.get_y_size (); y_pixel_number++)
    {
        for (size_t x_pixel_number = 0; x_pixel_number < graphic_system.get_x_size (); x_pixel_number++)
        {

            if (SQUARE (x_center_ + graphic_system.get_x_center () - x_pixel_number) +
                SQUARE (graphic_system.get_y_center () - y_center_ - y_pixel_number) <=
                SQUARE (radius_))
            {
                set_color (&pixel_color, lighting.get_color (), ambient_coeff, color_,
                           x_center_, y_center_,
                           radius_,
                           lighting.get_x (),
                           lighting.get_y (),
                           lighting.get_z (),
                           x_pixel_number - graphic_system.get_x_center (),
                           graphic_system.get_y_center () - y_pixel_number);

                    memcpy (pixels + 4 * (x_pixel_number + y_pixel_number * graphic_system.get_x_size ()), &pixel_color, sizeof (int));
                    continue;
            }
            int black = 0x00000000;
            memcpy (pixels + 4 * (x_pixel_number + y_pixel_number * graphic_system.get_x_size ()), &black, sizeof (int));
        }
    }

    return pixels;
}

void set_color (int* color, int light_color, double ambient_coeff, int sphere_color,
                int center_sphere_x, int center_sphere_y, size_t radius,
                int light_x, int light_y, int light_z,
                int point_sphere_x, int point_sphere_y)
{
    int point_sphere_height = sqrt (radius * radius -
                                    (center_sphere_x - point_sphere_x) * (center_sphere_x - point_sphere_x) -
                                    (center_sphere_y - point_sphere_y) * (center_sphere_y - point_sphere_y));

    Vector3 light_vector  (point_sphere_x      - light_x,
                           point_sphere_y      - light_y,
                           point_sphere_height - light_z);

    Vector3 normal_vector (center_sphere_x - point_sphere_x,
                           center_sphere_y - point_sphere_y,
                           0 - point_sphere_height); // Пока шар находится строго на уровне z = 0

    double cos_between = get_cos_between (light_vector, normal_vector);
    if (cos_between <= 0)
        cos_between = 0;


    printf ("aacolor == 0x%x\n", light_color);
    printf ("light_color & ALPHA_CHANNEL_MASK) >> ALPHA_SHIFT == 0x%x\n", (light_color & ALPHA_CHANNEL_MASK) >> ALPHA_SHIFT);
    printf ("(sphere_color & ALPHA_CHANNEL_MASK) >> ALPHA_SHIFT == 0x%x\n", (sphere_color & ALPHA_CHANNEL_MASK) >> ALPHA_SHIFT);
    int alpha_channel = ((light_color & ALPHA_CHANNEL_MASK) >> ALPHA_SHIFT) *
                        ((sphere_color & ALPHA_CHANNEL_MASK) >> ALPHA_SHIFT) *
                        (cos_between + ambient_coeff);
    printf ("aaalpha_channel == 0x%x\n", alpha_channel);
    alpha_channel = (alpha_channel << ALPHA_SHIFT) & ALPHA_CHANNEL_MASK;
    printf ("alpha_channel == 0x%x\n", alpha_channel);

    int red_channel   = ((light_color & RED_CHANNEL_MASK) >> RED_SHIFT) *
                        ((sphere_color & RED_CHANNEL_MASK) >> RED_SHIFT) *
                        (cos_between + ambient_coeff);
    red_channel = (red_channel << RED_SHIFT) & RED_CHANNEL_MASK;
    printf ("red_channel == 0x%x\n", red_channel);

    int green_channel   = ((light_color & GREEN_CHANNEL_MASK) >> GREEN_SHIFT) *
                          ((sphere_color & GREEN_CHANNEL_MASK) >> GREEN_SHIFT) *
                          (cos_between + ambient_coeff);
    green_channel = (green_channel << GREEN_SHIFT) & GREEN_CHANNEL_MASK;
    printf ("green_channel == 0x%x\n", green_channel);

    int blue_channel   = ((light_color & BLUE_CHANNEL_MASK) >> BLUE_SHIFT) *
                         ((sphere_color & BLUE_CHANNEL_MASK) >> BLUE_SHIFT) *
                         (cos_between + ambient_coeff);
    blue_channel = (blue_channel << BLUE_SHIFT) & BLUE_CHANNEL_MASK;
    printf ("blue_channel == 0x%x\n", blue_channel);

    *color = 0x6A000000 | red_channel | green_channel | blue_channel;
    printf ("color == 0x%x\n", *color);
}
