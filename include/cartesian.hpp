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

    Cartesian (const Cartesian& cartesian):
               x_min_    (cartesian.x_min_),
               x_max_    (cartesian.x_max_),
               y_min_    (cartesian.y_min_),
               y_max_    (cartesian.y_max_),
               x_center_ (cartesian.x_center_),
               y_center_ (cartesian.y_center_)
    {}

    void operator= (const Cartesian& source_cartesian);

    int get_x_center () const;
    int get_y_center () const;
};

#endif // CARTESIAN_HPP
