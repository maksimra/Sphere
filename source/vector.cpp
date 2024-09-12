#include "../include/vector.hpp"
#include "../include/compare_doubles.hpp"
#include <math.h>

const int    NUM_OF_DEGREES_IN_CIRCLE      = 360;
const int    NUM_OF_DEGREES_IN_RIGHT_ANGLE = 90;
const double PI                            = 3.14;
const int    COEFF_FOR_LENGTH_ARROWS       = 10;

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

// void Vector3::draw (sf::RenderWindow& window, double x_begin, double y_begin, size_t x_size_of_window, size_t y_size_of_window)
// {
//     float changed_x = (float) recalcul_x (x, x_size_of_window);
//     float changed_y = (float) recalcul_y (y, y_size_of_window);
//
//     //sf::Vertex vector_lines[NUM_OF_LINE_FOR_ARROW][NUM_OF_POINT_TO_LINE] = {};
// //
//     //get_lines (vector_lines[][NUM_OF_POINT_TO_LINE], this->get_x (), this->get_y (), x_size_of_window, y_size_of_window);
//
//     sf::Vertex main_line[] =
//     {
//         sf::Vertex(sf::Vector2f((float) recalcul_x (x_begin, x_size_of_window), (float) recalcul_y (y_begin, y_size_of_window))),
//         sf::Vertex(sf::Vector2f(changed_x, changed_y))
//     };
//
//     Vector3 arrow_vector_1 (*this + (get_perpendicular (*this, CLOCKWISE_DIRECTION) - *this) / COEFF_FOR_LENGTH_ARROWS);
//     printf ("angle2 == %lf\n", (arrow_vector_1 - *this).angle);
//     sf::Vertex arrow_line_1[] =
//     {
//         sf::Vertex(sf::Vector2f(changed_x, changed_y)),
//         sf::Vertex(sf::Vector2f((float) recalcul_x (arrow_vector_1.x, x_size_of_window), (float) recalcul_y (arrow_vector_1.y, y_size_of_window)))
//     };
//     Vector3 arrow_vector_2 (*this + (get_perpendicular (*this, COUNTERCLOCKWISE_DIRECTION) - *this) / COEFF_FOR_LENGTH_ARROWS);
//     printf ("angle == %lf\n", arrow_vector_2.angle);
//     sf::Vertex arrow_line_2[] =
//     {
//         sf::Vertex(sf::Vector2f(changed_x, changed_y)),
//         sf::Vertex(sf::Vector2f((float) recalcul_x (arrow_vector_2.x, x_size_of_window), (float) recalcul_y (arrow_vector_2.y, y_size_of_window)))
//     };
//     window.draw(main_line,    NUM_OF_POINT_TO_LINE, sf::Lines);
//     window.draw(arrow_line_1, NUM_OF_POINT_TO_LINE, sf::Lines);
//     window.draw(arrow_line_2, NUM_OF_POINT_TO_LINE, sf::Lines);
// }

Vector3 operator+ (Vector3 vector_1, Vector3 vector_2)
{
    return vector_1 += vector_2;
}

Vector3 operator- (Vector3 vector_1, Vector3 vector_2)
{
    return vector_1 -= vector_2;
}

Vector3 Vector3::operator/ (double divider)
{
    x /= divider;
    y /= divider;
    z /= divider;

    return *this;
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
