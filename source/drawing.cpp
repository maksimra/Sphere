#include <string.h>
#include <stdio.h>

#include "../include/drawing.hpp"
#include "../include/vector.hpp"
#include "../include/sphere.hpp"

const size_t N_BYTES_FOR_PIXEL = 4;

static FILE* log_file = stderr;

void drawing_set_log_file (FILE* file)
{
    if (file)
        log_file = file;
}

int GraphicSystem::get_x_center () const
{
    return coordinate_system_.get_x_center ();
}

int GraphicSystem::get_y_center () const
{
    return coordinate_system_.get_y_center ();
}

size_t GraphicSystem::get_x_size () const
{
    return size_x_;
}

size_t GraphicSystem::get_y_size () const
{
    return size_y_;
}

int recalcul_x (Cartesian coordinate_system, int x, size_t size_x_win)
{
    return (int) size_x_win / 2 + coordinate_system.get_x_center () + x;
}

int recalcul_y (Cartesian coordinate_system, int y, size_t size_y_win)
{
    return (int) size_y_win / 2 - (coordinate_system.get_y_center () + y);
}

GraphicSystem::GraphicSystem (const Cartesian& coordinate_system, size_t size_x, size_t size_y):
                              coordinate_system_ (coordinate_system),
                              size_x_ (size_x),
                              size_y_ (size_y),
                              window (sf::VideoMode ((unsigned int) size_x, (unsigned int) size_y), "MyWindow")
                              {}

// void GraphicSystem::operator= (const GraphicSystem& source_graphic_system)
// {
//     coordinate_system_ = source_graphic_system.coordinate_system_;
//     window (sf::VideoMode (source_graphic_system.size_x_,
//                            source_graphic_system.size_y_),
//                            "MyWindow");
//     size_x_ = source_graphic_system.size_x_;
//     size_y_ = source_graphic_system.size_y_;
// }

void GraphicSystem::draw_line (int x_1, int y_1, int x_2, int y_2)
{
    int relative_x_1 = recalcul_x (coordinate_system_, x_1, size_x_);
    int relative_x_2 = recalcul_x (coordinate_system_, x_2, size_x_);
    int relative_y_1 = recalcul_y (coordinate_system_, y_1, size_y_);
    int relative_y_2 = recalcul_y (coordinate_system_, y_2, size_y_);

    sf::Vertex line[] =
    {
        sf::Vertex (sf::Vector2f ((float) relative_x_1, (float) relative_y_1)),
        sf::Vertex (sf::Vector2f ((float) relative_x_2, (float) relative_y_2))
    };

    window.draw (line, NUM_POINT_TO_LINE, sf::Lines);
}

void GraphicSystem::draw_pixels (unsigned char* pixels)
{
    assert (pixels);
    window.clear();

    sf::Texture texture;
    texture.create((unsigned int) size_x_, (unsigned int) size_y_);
    texture.update (pixels);
    sf::Sprite sprite(texture);
    window.draw (sprite);
    window.display();
}

void GraphicSystem::win_clear ()
{
    window.clear (sf::Color::Blue);
}

void GraphicSystem::win_process_event ()
{
    sf::Event event;
    while (window.pollEvent (event))
    {
        if (event.type == sf::Event::Closed)
            window.close ();

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {

            }
        }
    }
}

bool GraphicSystem::win_open ()
{
    return window.isOpen();
}

void GraphicSystem::win_display ()
{
    window.display ();
}
