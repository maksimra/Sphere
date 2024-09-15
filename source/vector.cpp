#include <math.h>
#include <stdio.h>

#include "../include/vector.hpp"
#include "../include/compare_doubles.hpp"

const int    NUM_OF_DEGREES_IN_CIRCLE      = 360;
const int    NUM_OF_DEGREES_IN_RIGHT_ANGLE = 90;
const double PI                            = 3.14;
const int    COEFF_FOR_LENGTH_ARROWS       = 10;

static FILE* log_file = stderr;

void vector_set_log_file (FILE* file)
{
    if (file)
        log_file = file;
}

Vector3& Vector3::operator= (const Vector3& source_vector)
{
    x = source_vector.x;
    y = source_vector.y;
    z = source_vector.z;
    return *this;
}

Vector3 Vector3::operator+= (Vector3 additional_vector)
{
    x += additional_vector.x;
    y += additional_vector.y;
    z += additional_vector.z;

    return *this;
}

Vector3 Vector3::operator-= (Vector3 additional_vector)
{
    x -= additional_vector.x;
    y -= additional_vector.y;
    z -= additional_vector.z;

    return *this;
}

Vector3  Vector3::operator*= (double multiplier)
{
    x *= multiplier;
    y *= multiplier;
    z *= multiplier;

    return *this;
}

Vector3 operator+ (Vector3 vector_1, Vector3 vector_2)
{
    return vector_1 += vector_2;
}

Vector3 operator- (Vector3 vector_1, Vector3 vector_2)
{
    return vector_1 -= vector_2;
}

Vector3 Vector3::operator/ (double divider) const
{
    return Vector3 (x / divider,
                    y / divider,
                    z / divider);
}

Vector3 Vector3::operator* (double multiplier) const
{
    return Vector3 (x * multiplier,
                    y * multiplier,
                    z * multiplier);
}

double Vector3::get_length () const
{
    return sqrt (x * x + y * y + z * z);
}

double get_cos_between (const Vector3& vector1, const Vector3& vector2)
{
    double scalar_product = vector1.get_x () * vector2.get_x () +
                            vector1.get_y () * vector2.get_y () +
                            vector1.get_z () * vector2.get_z ();

    return scalar_product / (vector1.get_length () * vector2.get_length ());
}

double Vector3::get_x () const
{
    return x;
}

double Vector3::get_y () const
{
    return y;
}

double Vector3::get_z () const
{
    return z;
}

Vector3 multiple_of_elements (const Vector3& vector1, const Vector3& vector2)
{
    return Vector3 (vector1.get_x () * vector2.get_x (),
                    vector1.get_y () * vector2.get_y (),
                    vector1.get_z () * vector2.get_z ());
}
