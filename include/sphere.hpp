#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <assert.h>
#include <stdio.h>
#include <stdint.h>

#include "lighting.hpp"
#include "drawing.hpp"
#include "vector.hpp"

const uint32_t ALPHA_CHANNEL_MASK = 0xFF000000; // поменять потом int на uint32_t
const int      ALPHA_SHIFT        = 24;
const uint32_t BLUE_CHANNEL_MASK  = 0x00FF0000;
const int      BLUE_SHIFT         = 16;
const uint32_t GREEN_CHANNEL_MASK = 0x0000FF00;
const int      GREEN_SHIFT        = 8;
const uint32_t RED_CHANNEL_MASK   = 0x000000FF;
const int      RED_SHIFT          = 0;

const size_t SIZE_FOR_ONE_COLOR = 4; // спросить про две константы одинаковые здесь и в lighting

class GraphicSystem;
class Lighting;

class Sphere
{
    size_t  radius_;
    Vector3 color_;
    int x_center_, y_center_;
public:
    Sphere (size_t radius, int x_center, int y_center, Vector3 color):
            radius_ (radius), color_ (color), x_center_ (x_center), y_center_ (y_center) {}

    void   set_radius (size_t new_radius);
    size_t get_radius   () const;
    int    get_x_center () const;
    int    get_y_center () const;

    void get_sphere_pixels (uint8_t* pixels, const Lighting& lighting, const GraphicSystem& graphic_system,
                            double ambient_coeff, int point_view_height, int glare_multiplier);

};


void set_color (Vector3* sum_color, const Vector3& light_color, const Vector3& sphere_color,
                double ambient_coeff, int point_view_height, int glare_multiplier,
                int center_sphere_x, int center_sphere_y, size_t radius,
                int light_x, int light_y, int light_z,
                int point_sphere_x, int point_sphere_y);

void set_pixel (uint8_t* pixels, const Vector3& pixel_color,
                size_t x_pixel_number, size_t y_pixel_number,
                size_t x_window_size);

void fill_color (uint32_t* color, const Vector3& rgb_vector);

void sphere_set_log_file (FILE* file);

#endif // SPHERE_HPP
