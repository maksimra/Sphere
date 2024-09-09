#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include "lighting.hpp"
#include "drawing.hpp"

const size_t SIZE_FOR_ONE_COLOR = 3; // спросить про две константы одинаковые здесь и в lighting

class Sphere
{
    size_t  radius;
    const uint8_t* color;
    int x_center, y_center;
public:
    Sphere (size_t radius, int x_center, int y_center, const uint8_t* color):
            radius (radius), x_center (x_center), y_center (y_center), color (color)
    {}

    void   set_radius (size_t new_radius);
    size_t get_radius ();
    int    get_x_center ();
    int    get_y_center ();
};

uint8_t* get_sphere_pixels (Sphere sphere, Lighting lighting, GraphicSystem graphic_system);

int Sphere::get_x_center ()
{
    return x_center;
}

int Sphere::get_y_center ()
{
    return y_center;
}

size_t Sphere::get_radius ()
{
    return radius;
}

void Sphere::set_radius (size_t new_radius)
{
    radius = new_radius;
}


#endif // SPHERE_HPP
