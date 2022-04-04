#include <iostream>
#include <SDL2/SDL.h>

#include "ConwayGrid.hpp"

using namespace std;

void draw_grid_to_surface(SDL_Surface *screenSurface, ConwayGrid *grid) {
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ));
    for (int y = 0; y < grid->height; y++) {
        for (int x = 0; x < grid->width; x++) {
            Uint32 colour = grid->cell_alive_at(x, y)
                            ? SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00)
                            : SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF);
            SDL_Rect rectangle = {
                .x = x * grid->cell_width,
                .y = y * grid->cell_height,
                .w = grid->cell_width - 1,
                .h = grid->cell_height - 1
            };
            SDL_FillRect(screenSurface, &rectangle, colour);
        }
    }
}

int main(int argc, char** argv) {
    ConwayGrid grid;
    if (argc > 1) {
        grid.load_from_file(argv[1]);
    } else {
        grid.load_from_file("gosper.cwy");
    }

    grid.run();

    int rc = SDL_Init(SDL_INIT_VIDEO);

    if (rc != 0) {
        throw exception();
    }

    SDL_Window *window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                        grid.cell_width * grid.width, grid.cell_width * grid.width,
                                        SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP);
    if (window == NULL) {
        throw exception();
    }

    // this doesn't work and I don't understand why
    SDL_RaiseWindow(window);
    SDL_SetWindowInputFocus(window);

    SDL_Surface *screenSurface = SDL_GetWindowSurface(window);

    draw_grid_to_surface(screenSurface, &grid);
    SDL_UpdateWindowSurface(window);

    SDL_Event e;
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                    case SDLK_q:
                        quit = true;
                        break;
                    case SDLK_r:
                        grid.run();
                        break;
                    case SDLK_p:
                        grid.pause();
                        break;        
                }
            }
            if (e.type == SDL_MOUSEBUTTONUP) {
                int cell_x = e.button.x / grid.cell_width;
                int cell_y = e.button.y / grid.cell_height;

                grid.invert_cell(cell_x, cell_y);
            }
        }

        Uint32 time_before_step = SDL_GetTicks();
        grid.step();
        Uint32 time_after_step_before_draw = SDL_GetTicks();
        cout << "Time to step: " << (time_after_step_before_draw - time_before_step) << endl;
        draw_grid_to_surface(screenSurface, &grid);
        SDL_UpdateWindowSurface(window);
        Uint32 time_after_draw = SDL_GetTicks();
        cout << "Time to draw: " << (time_after_draw - time_after_step_before_draw) << endl;
    }

    return 0;
}
