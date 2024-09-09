#include <stdio.h>
#include "include/cartesian.hpp"
#include "include/vector.hpp"
#include "include/drawing.hpp"
#include "include/lighting.hpp"
#include "include/sphere.hpp"

// Спросить, не лучше ли внутри мейна константы определять
const size_t  SIZE_X_WINDOW                = 600;
const size_t  SIZE_Y_WINDOW                = 600;
const int     X_CENTER                     = 0;
const int     Y_CENTER                     = 0;
const size_t  SPHERE_RADIUS                = 200;
const int     SPHERE_CENTER_X              = 0;
const int     SPHERE_CENTER_Y              = 0;
const uint8_t SPHERE_COLOR[SIZE_ONE_COLOR] = {73, 51, 84}; // Серобуромалиновый
const int     LIGHT_X                      = 250;
const int     LIGHT_Y                      = 250;
const uint8_t LIGHT_BRIGHT                 = 0xFF;
const uint8_t LIGHT_COLOR[SIZE_ONE_COLOR] = {14, 41, 64};

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

    Lighting lighting (LIGHT_X, LIGHT_Y, LIGHT_BRIGHT, LIGHT_COLOR);

    uint8_t* pixels = get_sphere_pixels (sphere, lighting, graphic_system);

    while (graphic_system.win_open ())
    {
        graphic_system.win_process_event ();
        graphic_system.draw_pixels (pixels);
        window.display ();
    }

    free (pixels); // придумать, как пофиксить

    return 0;
}
