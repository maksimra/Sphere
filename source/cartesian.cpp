#include "../include/cartesian.hpp"

int Cartesian::get_x_center () const
{
    return x_center_;
}

int Cartesian::get_y_center () const
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
