#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include "lighting.hpp"
#include "drawing.hpp"

const int ALPHA_CHANNEL_MASK = 0xFF000000; // поменять потом int на uint32_t
const int ALPHA_SHIFT        = 24;
const int BLUE_CHANNEL_MASK  = 0x00FF0000;
const int BLUE_SHIFT         = 16;
const int GREEN_CHANNEL_MASK = 0x0000FF00;
const int GREEN_SHIFT        = 8;
const int RED_CHANNEL_MASK   = 0x000000FF;
const int RED_SHIFT          = 0;

const size_t SIZE_FOR_ONE_COLOR = 4; // спросить про две константы одинаковые здесь и в lighting

class GraphicSystem;
class Lighting;

class Sphere
{
    size_t  radius_;
    int color_;
    int x_center_, y_center_;
public:
    Sphere (size_t radius, int x_center, int y_center, int color):
            radius_ (radius), color_ (color), x_center_ (x_center), y_center_ (y_center) {}

    void   set_radius (size_t new_radius);
    size_t get_radius   () const;
    int    get_x_center () const;
    int    get_y_center () const;
    int    get_rgba     () const;

    uint8_t* get_sphere_pixels (const Lighting& lighting, const GraphicSystem& graphic_system, const double ambient_coeff);

};


void set_color (int* color, int light_color, double ambient_coeff, int sphere_color,
                int center_sphere_x, int center_sphere_y, size_t radius,
                int light_x, int light_y, int light_z,
                int point_sphere_x, int point_sphere_y);

#endif // SPHERE_HPP
