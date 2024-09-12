#include <stdio.h>
#include "include/cartesian.hpp"
#include "include/vector.hpp"
#include "include/drawing.hpp"
#include "include/lighting.hpp"
#include "include/sphere.hpp"

// Спросить, не лучше ли внутри мейна константы определять
const size_t  SIZE_X_WINDOW   = 1000;
const size_t  SIZE_Y_WINDOW   = 1000;
const int     X_CENTER        = SIZE_X_WINDOW / 2;
const int     Y_CENTER        = SIZE_Y_WINDOW / 2;
const size_t  SPHERE_RADIUS   = 400;
const int     SPHERE_CENTER_X = 0;
const int     SPHERE_CENTER_Y = 0;
const int     SPHERE_COLOR    = 0xFFFF00FF;
const int     LIGHT_X         = -500;
const int     LIGHT_Y         = 600;
const int     LIGHT_Z         = 700;
const int     LIGHT_COLOR     = 0xFF00F0FF;
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

    Sphere sphere (SPHERE_RADIUS, SPHERE_CENTER_X, SPHERE_CENTER_Y, SPHERE_COLOR);

    Lighting lighting (LIGHT_X, LIGHT_Y, LIGHT_Z, LIGHT_COLOR);

    uint8_t* pixels = sphere.get_sphere_pixels (lighting, graphic_system, AMBIENT_COEFF);
    graphic_system.draw_pixels (pixels);
    graphic_system.win_display ();
    //uint8_t* pixels = NULL; // подумать насчёт этого

    while (graphic_system.win_open ())
    {
        graphic_system.win_process_event ();
        // pixels = sphere.get_sphere_pixels (lighting, graphic_system);
        // graphic_system.draw_pixels (pixels);
        // graphic_system.win_display ();
    }

    free (pixels); // придумать, как пофиксить

    return 0;
}
