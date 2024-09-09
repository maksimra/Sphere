#include "../include/vector.hpp"

#define ANGLE_IN_RAD(angle) 2 * PI / NUM_OF_DEGREES_IN_CIRCLE * angle

const int    NUM_OF_DEGREES_IN_CIRCLE      = 360;
const int    NUM_OF_DEGREES_IN_RIGHT_ANGLE = 90;
const double PI                            = 3.14;
const int    COEFF_FOR_LENGTH_ARROWS       = 10;

void Vector2::operator= (const Vector2& source_vector)
{
    cur_mode = source_vector.cur_mode;
    x = source_vector.x;
    y = source_vector.y;
    angle = source_vector.angle;
    length = source_vector.length;
}

Vector2 Vector2::operator+= (Vector2 additional_vector)
{
    if (cur_mode != VECTOR_MODE_CARTESIAN)
    {
        this->upload_cartesian_mode ();
        cur_mode = VECTOR_MODE_CARTESIAN;
    }
    x += additional_vector.x;
    y += additional_vector.y;

    return *this;
}

Vector2 Vector2::operator-= (Vector2 additional_vector)
{
    if (cur_mode != VECTOR_MODE_CARTESIAN)
    {
        this->upload_cartesian_mode ();
        cur_mode = VECTOR_MODE_CARTESIAN;
    }
    x -= additional_vector.x;
    y -= additional_vector.y;

    return *this;
}

Vector2 Vector2::rotate (double alpha)
{
    if (cur_mode != VECTOR_MODE_POLAR)
    {
        this->upload_polar_mode ();
        cur_mode = VECTOR_MODE_POLAR;
    }
    angle = (int)(angle - alpha) % NUM_OF_DEGREES_IN_CIRCLE;
    return *this;
}

// void Vector2::draw (sf::RenderWindow& window, double x_begin, double y_begin, size_t x_size_of_window, size_t y_size_of_window)
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
//     Vector2 arrow_vector_1 (*this + (get_perpendicular (*this, CLOCKWISE_DIRECTION) - *this) / COEFF_FOR_LENGTH_ARROWS);
//     printf ("angle2 == %lf\n", (arrow_vector_1 - *this).angle);
//     sf::Vertex arrow_line_1[] =
//     {
//         sf::Vertex(sf::Vector2f(changed_x, changed_y)),
//         sf::Vertex(sf::Vector2f((float) recalcul_x (arrow_vector_1.x, x_size_of_window), (float) recalcul_y (arrow_vector_1.y, y_size_of_window)))
//     };
//     Vector2 arrow_vector_2 (*this + (get_perpendicular (*this, COUNTERCLOCKWISE_DIRECTION) - *this) / COEFF_FOR_LENGTH_ARROWS);
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

Vector2 operator+ (Vector2 vector_1, Vector2 vector_2)
{
    if (vector_1.get_vector_mode () != VECTOR_MODE_CARTESIAN)
    {
        vector_1.upload_cartesian_mode ();
    }
    if (vector_2.get_vector_mode () != VECTOR_MODE_CARTESIAN)
    {
        vector_2.upload_cartesian_mode ();
    }

    return vector_1 += vector_2;
}

Vector2 operator- (Vector2 vector_1, Vector2 vector_2)
{
    if (vector_1.get_vector_mode () != VECTOR_MODE_CARTESIAN)
    {
        vector_1.upload_cartesian_mode ();
    }
    if (vector_2.get_vector_mode () != VECTOR_MODE_CARTESIAN)
    {
        vector_2.upload_cartesian_mode ();
    }

    return vector_1 -= vector_2;
}

Vector2 Vector2::operator/ (int divider)
{
    if (cur_mode == VECTOR_MODE_CARTESIAN)
    {
        x /= divider;
        y /= divider;
    }
    else
    {
        length /= divider;
    }
    return *this;
}

double Vector2::get_angle ()
{
    if (cur_mode != VECTOR_MODE_POLAR)
    {
        this->upload_polar_mode ();
        cur_mode = VECTOR_MODE_POLAR;
    }

    return angle;
}

double Vector2::get_length ()
{
    if (cur_mode != VECTOR_MODE_POLAR)
    {
        this->upload_polar_mode ();
        cur_mode = VECTOR_MODE_POLAR;
    }

    return length;
}

VectorMode Vector2::get_vector_mode ()
{
    return cur_mode;
}

void Vector2::upload_cartesian_mode ()
{
    x = length * cos (ANGLE_IN_RAD (angle));
    y = length * sin (ANGLE_IN_RAD (angle));
}

void Vector2::upload_polar_mode ()
{
    if (compare_doubles (x, 0) != 0)
        angle = atan (y / x);
    else if (y > 0)
        angle = NUM_OF_DEGREES_IN_RIGHT_ANGLE;
    else if (y < 0)
        angle = NUM_OF_DEGREES_IN_CIRCLE - NUM_OF_DEGREES_IN_RIGHT_ANGLE;

    length = sqrt (y * y + x * x);
}

Vector2 get_perpendicular (Vector2 vector)
{
    return vector.rotate (NUM_OF_DEGREES_IN_RIGHT_ANGLE);
}
