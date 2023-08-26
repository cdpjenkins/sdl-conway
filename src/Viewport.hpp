#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include <SDL2/SDL.h>

#include "Grid.hpp"

class Viewport {
public:
    Viewport(float cell_size);

    void render_grid(SDL_Renderer *renderer, Grid *grid) const;
    void zoom_in();
    void zoom_out();
    void adjust_zoom(float dDist);
    float get_width() const;
    float get_height() const;
    void screen_coords_to_grid_coords(int x, int y, int *grid_x, int *grid_y) const;

private:
    float width, height;

    float cell_size;
};

#endif // VIEWPORT_HPP
