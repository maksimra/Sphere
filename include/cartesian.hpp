#ifndef CARTESIAN_HPP
#define CARTESIAN_HPP

#include <stdio.h>

class Cartesian
{
    size_t x_min_,    x_max_;
    size_t y_min_,    y_max_;
    int x_center_, y_center_;

public:
    Cartesian (size_t x_min, size_t x_max, size_t y_min, size_t y_max, int x_center, int y_center):
               x_min_    (x_min),    x_max_    (x_max),
               y_min_    (y_min),    y_max_    (y_max),
               x_center_ (x_center), y_center_ (y_center) {}

    void operator= (const Cartesian& source_cartesian);

    int get_x_center ();
    int get_y_center ();
};

int Cartesian::get_x_center ()
{
    return x_center_;
}

int Cartesian::get_y_center ()
{
    return y_center_;
}

void Cartesian::operator= (const Cartesian& source_cartesian)
{
    x_min_    = source_cartesian.x_min_;
    y_min_    = source_cartesian.y_min_;
    x_max_    = source_cartesian.x_max_;
    y_max_    = source_cartesian.y_max_;
    x_center_ = source_cartesian.x_center_;
    y_center_ = source_cartesian.y_center_;
}

#endif // CARTESIAN_HPP
