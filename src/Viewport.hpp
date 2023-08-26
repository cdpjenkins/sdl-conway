#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include <SDL2/SDL.h>

#include "Grid.hpp"

class Viewport {
public:
    Viewport(float width, float height, float cell_size, float zoom);

    void render_grid(SDL_Renderer *renderer, Grid *grid);
    void zoom_in();
    void zoom_out();
    void adjust_zoom(float dDist);
    float get_width();
    float get_height();
    void screen_coords_to_grid_coords(int x, int y, int *grid_x, int *grid_y);  

private:
    float width, height;
    float zoom;

    float cell_size;
};

#endif // VIEWPORT_HPP
