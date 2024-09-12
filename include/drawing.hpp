#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include "cartesian.hpp"
#include "sphere.hpp"
#include <SFML/Graphics.hpp>
#include "lighting.hpp"
#include <assert.h>

#define SQUARE(x) (x) * (x) // поменять

const size_t NUM_POINT_TO_LINE = 2;

class Sphere;

class GraphicSystem
{
    Cartesian coordinate_system_;
    size_t size_x_, size_y_;
    sf::RenderWindow window;

public:

    GraphicSystem (const Cartesian& coordinate_system, size_t size_x, size_t size_y);

    void operator=   (const GraphicSystem& source_graphic_system);

    void draw_line   (int x_1, int y_1, int x_2, int y_2);
    void draw_pixels (uint8_t* pixels);

    bool win_open ();
    void win_process_event ();
    void win_display ();
    void win_clear ();

    size_t get_x_size   () const;
    size_t get_y_size   () const;
    size_t get_x_center () const;
    size_t get_y_center () const;
};

int      recalcul_x (Cartesian coordinate_system, int x, size_t size_x_win);

int      recalcul_y (Cartesian coordinate_system, int y, size_t size_y_win);


#endif // GRAPHIC_HPP
