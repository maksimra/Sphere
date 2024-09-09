#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include "cartesian.hpp"
#include <SFML/Graphics.hpp>
#include <assert.h>

#define SQUARE(x) (x) * (x)

const size_t NUM_POINT_TO_LINE = 2;

class GraphicSystem
{
    Cartesian coordinate_system_;
    size_t size_x_, size_y_;
    sf::RenderWindow window;

public:

    GraphicSystem    (Cartesian coordinate_system_, size_t size_x, size_t size_y);

    void operator=   (const GraphicSystem& source_graphic_system);

    void draw_line   (int x_1, int y_1, int x_2, int y_2);
    void draw_pixels (uint8_t* pixels);

    bool win_open ();
    void win_process_event ();

    size_t get_x_size ();
    size_t get_y_size ();
    size_t get_x_center ();
    size_t get_y_center ();
};

size_t GraphicSystem::get_x_center ()
{
    return coordinate_system_.get_x_center ();
}

size_t GraphicSystem::get_y_center ()
{
    return coordinate_system_.get_y_center ();
}

size_t GraphicSystem::get_x_size ()
{
    return size_x_;
}

size_t GraphicSystem::get_y_size ()
{
    return size_y_;
}

int recalcul_x (Cartesian coordinate_system, int x, size_t size_x_win)
{
    return size_x_win / 2 + coordinate_system.get_x_center () + x;
}

int recalcul_y (Cartesian coordinate_system, int y, size_t size_y_win)
{
    return size_y_win / 2 - (coordinate_system.get_y_center () + y);
}

GraphicSystem::GraphicSystem (Cartesian coordinate_system_, size_t size_x, size_t size_y):
                              coordinate_system_ (coordinate_system_),
                              size_x_ (size_x),
                              size_y_ (size_y),
                              window (sf::VideoMode (size_x, size_y), "MyWindow")
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
        sf::Vertex (sf::Vector2f (relative_x_1, relative_y_1)),
        sf::Vertex (sf::Vector2f (relative_x_2, relative_y_2))
    };

    window.draw (line, NUM_POINT_TO_LINE, sf::Lines);
}

void GraphicSystem::draw_pixels (uint8_t* pixels)
{
    assert (pixels != NULL); // Спросить насчёт того, как проверять массив пикселей на размер

    sf::Texture texture;
    texture.create(size_x_, size_y_);
    texture.update (pixels);
    sf::Sprite sprite(texture);
    window.draw (sprite);
}

// Пока сделал просто равномерное раскрашивание сферы. Присутствует говнокод
//void GraphicSystem::draw_sphere (Sphere sphere, Lighting lighting, int x_center, int y_center)
//{
//    uint8_t* pixels = (uint8_t*) calloc (size_x_ * size_y_ * N_BYTES_FOR_PIXEL, sizeof(uint8_t));
//
//    for (size_t y_pixel_number; y_pixel_number < size_y_; y_pixel_number++)
//    {
//        for (size_t x_pixel_number; x_pixel_number < size_x_; x_pixel_number++)
//        {
//            if (SQUARE (sphere.get_x_center() + coordinate_system_.get_x_center () - x_pixel_number) +
//                SQUARE (coordinate_system_.get_y_center () - sphere.get_y_center () - y_pixel_number) <=
//                SQUARE (sphere.get_radius))
//            {
//                int green = 0xFF00FF00;
//                memcpy (pixels + 4 * x_pixel_number + y_pixel_number, &green, sizeof (int));
//                continue;
//            }
//            int black = 0x00000000;
//            memcpy (pixels + 4 * x_pixel_number + y_pixel_number, &green, sizeof (int));
//        }
//    }
//
//    sf::Texture texture;
//    texture.create(size_x_, size_y_);
//    texture.update (pixels);
//    sf::Sprite sprite(texture);
//    window.draw (sprite);
//}

void GraphicSystem::win_process_event ()
{
    sf::Event event;
    while (window.pollEvent (event))
    {
        if (event.type == sf::Event::Closed)
            window.close ();
    }
}

bool GraphicSystem::win_open ()
{
    return window.isOpen();
}


#endif // GRAPHIC_HPP
