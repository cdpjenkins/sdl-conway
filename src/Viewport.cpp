#include <iostream>

#include "Viewport.hpp"

using namespace std;

Viewport::Viewport(Grid *grid, float cell_size)
    : width{static_cast<int>(Grid::width * cell_size)},
      height{static_cast<int>(Grid::height * cell_size)},
      cell_size{cell_size},
      grid(grid) {}

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

void Viewport::render_grid_delta(SDL_Renderer *renderer, Grid *grid) const {
//
//    for (auto & cell : grid->updated_indices) {
////        cout << "(" << cell.x << "," << cell.y << "): " << cell.alive << " ";
//
//        float x = static_cast<float>(cell.x) * cell_size;
//        float y = static_cast<float>(cell.y) * cell_size;
//
//        if (cell.alive) {
//            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
//        } else {
//            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
//        }
//
//        SDL_Rect rectangle = {
//                .x = (int)x,
//                .y = (int)y,
//                .w = (int)(cell_size - 1),
//                .h = (int)(cell_size - 1)
//        };
//        SDL_RenderFillRect(renderer, &rectangle);
//
//    }
////    cout << endl;
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

int Viewport::get_width() const {
    return width;
}

int Viewport::get_height() const {
    return height;
}

void Viewport::screen_coords_to_grid_coords(int x, int y, int *grid_x, int *grid_y) const {
    *grid_x = static_cast<int>(static_cast<float>(x) / cell_size);
    *grid_y = static_cast<int>(static_cast<float>(y) / cell_size);
}
