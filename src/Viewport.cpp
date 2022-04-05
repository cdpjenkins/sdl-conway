#include "Viewport.hpp"

Viewport::Viewport(float width, float height, float centre_x, float centre_y, float zoom) {
    this->width = width;
    this->height = height;
    this->centre_x = centre_x;
    this->centre_y = centre_y;
    this->zoom = zoom;
}

void Viewport::render_grid(SDL_Renderer *renderer, ConwayGrid *grid) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    int cell_size_to_render = cell_size > 1 ? cell_size - 1 : cell_size;
    for (int y = 0; y < grid->height; y++) {
        for (int x = 0; x < grid->width; x++) {
            if (grid->cell_alive_at(x, y)) {
                SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

                SDL_Rect rectangle = {
                    .x = x * cell_size,
                    .y = y * cell_size,
                    .w = cell_size - 1,
                    .h = cell_size - 1
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

float Viewport::get_width() {
    return width;
}

float Viewport::get_height() {
    return height;
}

int Viewport::get_cell_size() {
    return cell_size;
}

void Viewport::screen_coords_to_grid_coords(int x, int y, int *grid_x, int *grid_y) {
    *grid_x = x / cell_size;
    *grid_y = y / cell_size;
}
