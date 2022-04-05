#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include <SDL2/SDL.h>

#include "ConwayGrid.hpp"

class Viewport {
public:
    Viewport(float width, float height, float centre_x, float centre_y, float zoom);

    void render_grid(SDL_Renderer *renderer, ConwayGrid *grid);
    void zoom_in();
    void zoom_out();
    void adjust_zoom(float dDist);
    float get_width();
    float get_height();
    void screen_coords_to_grid_coords(int x, int y, int *grid_x, int *grid_y);  

private:
    float width, height;
    float centre_x, centre_y;
    float zoom;

    float cell_size = 4;
};

#endif // VIEWPORT_HPP
