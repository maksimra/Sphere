#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <math.h>
#include "compare_doubles.hpp"

enum VectorMode
{
    VECTOR_MODE_CARTESIAN = 1,
    VECTOR_MODE_POLAR     = 2
};

class Vector2
{
    enum VectorMode cur_mode;
    double x;
    double y;
    double angle;
    double length;

public:
    Vector2 (double first_value, double second_value):
             cur_mode (VECTOR_MODE_CARTESIAN), x (first_value),    y (second_value),
             angle (0),                        length (0)          {}

    Vector2 (const Vector2& vector):
             cur_mode (vector.cur_mode), x (vector.x), y (vector.y),
             angle (vector.angle), length (vector.length) {}

    Vector2 ():
             cur_mode (VECTOR_MODE_CARTESIAN), x (0), y (0),
             angle    (0),                     length (0) {}

    Vector2 operator+= (Vector2 additional_vector);
    Vector2 operator-= (Vector2 additional_vector);
    Vector2 operator/  (int divider);
    void    operator=  (const Vector2& source_vector);

    double     get_angle  ();
    double     get_length ();
    VectorMode get_vector_mode ();

    Vector2 rotate (double alpha);

    void upload_cartesian_mode ();
    void upload_polar_mode     ();
};

Vector2 operator+             (Vector2 vector_1, Vector2 vector_2);
Vector2 operator-             (Vector2 vector_1, Vector2 vector_2);
Vector2 get_perpendicular     (Vector2 vector);

#endif // VECTOR_HPP
