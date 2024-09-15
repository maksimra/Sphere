#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdio.h>

#include "../include/sphere.hpp"
#include "../include/lighting.hpp"
#include "../include/drawing.hpp"
#include "../include/vector.hpp"
#include "../include/square.hpp"
#include "../include/for_logs.hpp"

static FILE* log_file = stderr;

void sphere_set_log_file (FILE* file)
{
    if (file)
        log_file = file;
}

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

void Sphere::get_sphere_pixels (uint8_t* pixels, const Lighting& lighting, const GraphicSystem& graphic_system,
                                double ambient_coeff, int point_view_height, int glare_multiplier)
{
    Vector3 pixel_color {};
    for (size_t y_pixel_number = 0; y_pixel_number < graphic_system.get_y_size (); y_pixel_number++)
    {
        for (size_t x_pixel_number = 0; x_pixel_number < graphic_system.get_x_size (); x_pixel_number++)
        {
            if (square ((double) (x_center_ + graphic_system.get_x_center () - (int) x_pixel_number)) +
                square ((double) (graphic_system.get_y_center () - y_center_ - (int) y_pixel_number)) <=
                square ((double) radius_))
            {
                set_color (&pixel_color, lighting.get_color (), color_,
                           ambient_coeff, point_view_height, glare_multiplier,
                           x_center_, y_center_,
                           radius_,
                           lighting.get_x (),
                           lighting.get_y (),
                           lighting.get_z (),
                           (int) x_pixel_number - graphic_system.get_x_center (),
                           graphic_system.get_y_center () - (int) y_pixel_number);

                PRINTF ("pixel_color:\nR = %lf\nG = %lf\nB = %lf\n",
                        pixel_color.get_x (), pixel_color.get_y (), pixel_color.get_z ());

                set_pixel (pixels, pixel_color,
                           x_pixel_number, y_pixel_number,
                           graphic_system.get_x_size ());
            }
            else
            {
                set_pixel (pixels, Vector3 (0, 0, 0),
                           x_pixel_number, y_pixel_number,
                           graphic_system.get_x_size ());
            }
        }
    }
    for (int a = 0; a < graphic_system.get_x_size () * graphic_system.get_y_size (); a++)
    {
        PRINTF ("HUI 0x%x\n", *((uint32_t*) pixels + a));
    }
}

void set_pixel (uint8_t* pixels, const Vector3& pixel_color,
                size_t x_pixel_number, size_t y_pixel_number,
                size_t x_window_size)
{
    uint8_t red_channel   = (uint8_t) ((pixel_color.get_x () < UCHAR_MAX) ? pixel_color.get_x () : UCHAR_MAX);
    uint8_t green_channel = (uint8_t) ((pixel_color.get_y () < UCHAR_MAX) ? pixel_color.get_y () : UCHAR_MAX);
    uint8_t blue_channel  = (uint8_t) ((pixel_color.get_z () < UCHAR_MAX) ? pixel_color.get_z () : UCHAR_MAX);

    uint8_t color_channels[4] = {red_channel,
                                 green_channel,
                                 blue_channel,
                                 UCHAR_MAX}; // <---- Transparency

    PRINTF ("color_channel[4] = 0x%x\n", *((uint32_t*) color_channels));

    for (size_t n_channel = 0; n_channel < 4; n_channel++)
    {
        pixels[4 * (x_pixel_number + y_pixel_number * x_window_size) + n_channel] = color_channels[n_channel];
    }
    PRINTF ("pixels[%d] = 0x%x\n", 4 * (x_pixel_number + y_pixel_number * x_window_size),
                                  *(uint32_t*) (pixels + 4 * (x_pixel_number + y_pixel_number * x_window_size)));
}

void set_color (Vector3* sum_color, const Vector3& light_color, const Vector3& sphere_color,
                double ambient_coeff, int point_view_height, int glare_multiplier,
                int center_sphere_x, int center_sphere_y, size_t radius,
                int light_x, int light_y, int light_z,
                int point_sphere_x, int point_sphere_y)
{
    int point_sphere_height = (int) sqrt ((int) (radius * radius) -
                                    (center_sphere_x - point_sphere_x) * (center_sphere_x - point_sphere_x) -
                                    (center_sphere_y - point_sphere_y) * (center_sphere_y - point_sphere_y));

    Vector3 light_vector  (point_sphere_x      - light_x,
                           point_sphere_y      - light_y,
                           point_sphere_height - light_z);

    Vector3 normal_vector (center_sphere_x - point_sphere_x,
                           center_sphere_y - point_sphere_y,
                           0 - point_sphere_height);
                           // Шар находится строго на уровне z = 0

    double sphere_and_light_cos = get_cos_between (light_vector, normal_vector);
    if (sphere_and_light_cos <= 0)
        sphere_and_light_cos = 0;

    normal_vector *= - (sphere_and_light_cos * light_vector.get_length ()) / normal_vector.get_length ();

    Vector3 supportive_vector (light_vector.get_x () + normal_vector.get_x (),
                               light_vector.get_y () + normal_vector.get_y (),
                               light_vector.get_z () + normal_vector.get_z ());

    Vector3 reflected_vector (supportive_vector * 2 - light_vector);

    Vector3 viewer_vector (0 - point_sphere_x,
                           0 - point_sphere_y,
                           point_view_height - point_sphere_height);

    double viewer_and_light_cos = get_cos_between (reflected_vector, viewer_vector);
    if (viewer_and_light_cos <= 0)
        viewer_and_light_cos = 0;

    double glare_coeff = pow (viewer_and_light_cos, glare_multiplier);

    printf ("glare_coeff == %lf\n", glare_coeff);

    *sum_color = (multiple_of_elements (sphere_color, light_color) * (sphere_and_light_cos + ambient_coeff)
                 + light_color * glare_coeff) * UCHAR_MAX;

    PRINTF ("sum_color:\nR = %lf\nG = %lf\nB = %lf\n",
            (*sum_color).get_x (), (*sum_color).get_y (), (*sum_color).get_z ());
}
