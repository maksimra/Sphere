#include <stdio.h>
#include <stddef.h>

#include "include/cartesian.hpp"
#include "include/vector.hpp"
#include "include/drawing.hpp"
#include "include/lighting.hpp"
#include "include/sphere.hpp"


const size_t N_BYTES_FOR_PIXEL = 4;
const size_t SIZE_X_WINDOW     = 800;
const size_t SIZE_Y_WINDOW     = 800;
const int    X_CENTER          = SIZE_X_WINDOW / 2;
const int    Y_CENTER          = SIZE_Y_WINDOW / 2;
const size_t SPHERE_RADIUS     = 300;
const int    SPHERE_CENTER_X   = 0;
const int    SPHERE_CENTER_Y   = 0;
const int    LIGHT_X           = -250;
const int    LIGHT_Y           = 100;
const int    LIGHT_Z           = 1000;
const int    POINT_VIEW_HEIGHT = 800;
const int    GLARE_MULTIPLIER  = 8;
const double AMBIENT_COEFF     = 0.1;

int main()
{
    FILE* log_file = fopen ("log_file.txt", "w");
    if (!log_file)
        fprintf (stderr, "Ошибка открытия log file.\n");
    else
        setvbuf (log_file, NULL, _IONBF, 0);

    drawing_set_log_file (log_file); // <--- Pass NULL if you want write info in stderr
    sphere_set_log_file  (log_file);
    vector_set_log_file  (log_file);

    Cartesian coordinate_system (-SIZE_X_WINDOW / 2,
                                 SIZE_X_WINDOW  / 2,
                                 -SIZE_Y_WINDOW / 2,
                                 SIZE_Y_WINDOW  / 2,
                                 X_CENTER,
                                 Y_CENTER);

    GraphicSystem graphic_system (coordinate_system, SIZE_X_WINDOW,
                                                     SIZE_Y_WINDOW);

    Vector3 sphere_color (0.7, 0.1, 0.6);
    Vector3 light_color  (1, 1, 1.0);

    Sphere sphere (SPHERE_RADIUS, SPHERE_CENTER_X, SPHERE_CENTER_Y, sphere_color);

    Lighting lighting (LIGHT_X, LIGHT_Y, LIGHT_Z, light_color);

    uint8_t* pixels = (uint8_t*) calloc (graphic_system.get_x_size () * graphic_system.get_y_size () * N_BYTES_FOR_PIXEL, sizeof(uint8_t));


    sphere.get_sphere_pixels (pixels, lighting, graphic_system,
                              AMBIENT_COEFF, POINT_VIEW_HEIGHT, GLARE_MULTIPLIER);
    while(1) {
        graphic_system.draw_pixels (pixels);
        graphic_system.win_display ();
    }

    for (int a = 0; a < graphic_system.get_x_size () * graphic_system.get_y_size (); a++)
    {
        printf ("0x%x\n", *((int*) pixels + a));
    }

    while (graphic_system.win_open ())
    {
        graphic_system.win_process_event ();
    }

    free (pixels);

    return 0;
}
