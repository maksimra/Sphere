#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <math.h>
#include "compare_doubles.hpp"

enum VectorMode
{
    VECTOR_MODE_CARTESIAN = 1,
    VECTOR_MODE_POLAR     = 2
};

class Vector3
{
    double x;
    double y;
    double z;

public:
    Vector3 (double first_value, double second_value, double third_value):
             x (first_value), y (second_value), z (third_value) {}

    Vector3 (const Vector3& vector):
             x (vector.x), y (vector.y), z (vector.z){}

    Vector3 ():
             x (0), y (0), z (0) {}

    Vector3  operator+= (Vector3 additional_vector);
    Vector3  operator-= (Vector3 additional_vector);
    Vector3  operator/  (double divider);
    Vector3  operator*  (double multiplier);
    Vector3& operator=  (const Vector3& source_vector);

    double get_length () const;
    double get_x () const;
    double get_y () const;
    double get_z () const;
};

Vector3 multiple_of_elements (const Vector3& vector1, const Vector3& vector2);
Vector3 operator+            (Vector3 vector_1, Vector3 vector_2);
Vector3 operator-            (Vector3 vector_1, Vector3 vector_2);
double  get_cos_between      (const Vector3& vector1, const Vector3& vector2);

#endif // VECTOR_HPP
