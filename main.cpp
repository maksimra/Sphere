#include <stdio.h>
#include "include/cartesian.hpp"
#include "include/vector.hpp"
#include "include/drawing.hpp"
#include "include/lighting.hpp"
#include "include/sphere.hpp"

const size_t N_BYTES_FOR_PIXEL = 4;

// Спросить, не лучше ли внутри мейна константы определять
const size_t  SIZE_X_WINDOW   = 1000;
const size_t  SIZE_Y_WINDOW   = 1000;
const int     X_CENTER        = SIZE_X_WINDOW / 2;
const int     Y_CENTER        = SIZE_Y_WINDOW / 2;
const size_t  SPHERE_RADIUS   = 400;
const int     SPHERE_CENTER_X = 0;
const int     SPHERE_CENTER_Y = 0;
const int     LIGHT_X         = -500;
const int     LIGHT_Y         = 600;
const int     LIGHT_Z         = 700;
const double  AMBIENT_COEFF   = 0.05;

int main()
{
    Cartesian coordinate_system (-SIZE_X_WINDOW / 2,
                                 SIZE_X_WINDOW  / 2,
                                 -SIZE_Y_WINDOW / 2,
                                 SIZE_Y_WINDOW  / 2,
                                 X_CENTER,
                                 Y_CENTER);

    GraphicSystem graphic_system (coordinate_system, SIZE_X_WINDOW,
                                                     SIZE_Y_WINDOW);

    /*Создать вектор с цветами для света*/
    /*Создать вектор с цветами для сферы*/
    /*Передать вектора в конструкторы сферы и света*/
    /*Передать в функцию отрисовки пикселей информацию о прозрачности (или забить)*/

    Vector3 sphere_color (45, 54, 89);
    Vector3 light_color  (35, 119, 78);

    Sphere sphere (SPHERE_RADIUS, SPHERE_CENTER_X, SPHERE_CENTER_Y, sphere_color);

    Lighting lighting (LIGHT_X, LIGHT_Y, LIGHT_Z, light_color);

    unsigned char* pixels = (unsigned char*) calloc (graphic_system.get_x_size () * graphic_system.get_y_size () * N_BYTES_FOR_PIXEL, sizeof(uint8_t));

    sphere.get_sphere_pixels (pixels, lighting, graphic_system, AMBIENT_COEFF);

    while (graphic_system.win_open ())
    {
        graphic_system.win_process_event ();
        graphic_system.draw_pixels (pixels);
        graphic_system.win_display ();
    }

    free (pixels);

    return 0;
}
