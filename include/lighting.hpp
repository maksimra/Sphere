#ifndef LIGHTING_HPP
#define LIGHTING_HPP

#include "vector.hpp"

static const size_t SIZE_ONE_COLOR = 4;

class Lighting
{
    int x_;
    int y_;
    int z_;
    Vector3 color_;
public:
    Lighting (int x, int y, int z, Vector3 color):
              x_ (x), y_ (y), z_ (z), color_ (color) {}

    int get_x () const
    {
        return x_;
    }

    int get_y () const
    {
        return y_;
    }

    int get_z () const
    {
        return z_;
    }

    Vector3 get_color () const
    {
        return color_;
    }
};

#endif // LIGHTING_HPP
