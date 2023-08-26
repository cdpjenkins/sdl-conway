#include <iostream>

#include "Viewport.hpp"

using namespace std;

Viewport::Viewport(float cell_size)
    :   width{Grid::width * cell_size},
        height{Grid::height * cell_size},
        cell_size{cell_size}
{ }

void Viewport::render_grid(SDL_Renderer *renderer, Grid *grid) const {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    float sy = 0;
    for (int y = 0; y < Grid::height; y++, sy += cell_size) {
        float sx = 0;
        for (int x = 0; x < Grid::width; x++, sx += cell_size) {
            if (grid->cell_alive_at(x, y)) {
                SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

                SDL_Rect rectangle = {
                    .x = (int)sx,
                    .y = (int)sy,
                    .w = (int)(cell_size - 1),
                    .h = (int)(cell_size - 1)
                };
                SDL_RenderFillRect(renderer, &rectangle);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

void Viewport::zoom_in() {
    cell_size++;
}

void Viewport::zoom_out() {
    if (cell_size > 2) {
        cell_size--;
    }
}

void Viewport::adjust_zoom(float dDist) {
    cell_size *= (1 + dDist);
    cell_size = fmax(cell_size, 2.0f);

    cout << cell_size << endl;
}

float Viewport::get_width() const {
    return width;
}

float Viewport::get_height() const {
    return height;
}

void Viewport::screen_coords_to_grid_coords(int x, int y, int *grid_x, int *grid_y) const {
    *grid_x = static_cast<int>(static_cast<float>(x) / cell_size);
    *grid_y = static_cast<int>(static_cast<float>(y) / cell_size);
}
