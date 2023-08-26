#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include <SDL2/SDL.h>

#include <array>
using namespace std;

#include "Grid.hpp"

class Viewport {
public:
    explicit Viewport(Grid *grid, float cell_size);

    void render_grid(SDL_Renderer *renderer, Grid *grid) const;
    void render_grid_delta(SDL_Renderer *renderer, Grid *grid) const;
    void zoom_in();
    void zoom_out();
    void adjust_zoom(float dDist);
    int get_width() const;
    int get_height() const;
    void screen_coords_to_grid_coords(int x, int y, int *grid_x, int *grid_y) const;

    int width, height;
    float cell_size;

    Grid* grid;
};

#endif // VIEWPORT_HPP
