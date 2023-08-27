#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include <SDL2/SDL.h>

#include "Grid.hpp"

class Viewport {
public:
    explicit Viewport(float cell_size);

    void render_grid(SDL_Renderer *renderer, Grid &grid) const;
    void zoom_in();
    void zoom_out();
    void adjust_zoom(float dDist);
    int get_width() const;
    int get_height() const;
    void screen_coords_to_grid_coords(int x, int y, int &grid_x, int &grid_y) const;

private:
    int width, height;
    float cell_size;

};

#endif // VIEWPORT_HPP
