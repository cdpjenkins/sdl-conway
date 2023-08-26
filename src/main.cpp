#include <iostream>
#include <chrono>

#include <SDL2/SDL.h>

#include "Grid.hpp"
#include "Viewport.hpp"

using namespace std;

int main(int argc, char** argv) {
    Grid grid;
    if (argc > 1) {
        grid.load_from_file(argv[1]);
    } else {
        grid.load_from_file("gosper.cwy");
    }
    grid.run();

    Viewport viewport(2);

    SDL_SetHint(SDL_HINT_MOUSE_TOUCH_EVENTS, "1");
    int rc = SDL_Init(SDL_INIT_VIDEO);

    if (rc != 0) {
        throw exception();
    }

    SDL_Window *window = SDL_CreateWindow("SDL Conway for Mac!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                        viewport.get_width(), viewport.get_height(),
                                        SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP);
    if (window == nullptr) {
        throw exception();
    }

    // this doesn't work and I don't understand why
    SDL_RaiseWindow(window);
    SDL_SetWindowInputFocus(window);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    viewport.render_grid(renderer, &grid);
    SDL_UpdateWindowSurface(window);

    SDL_Event e;
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&e)){
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
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
                        case SDLK_PLUS:
                        case SDLK_EQUALS:
                            viewport.zoom_in();
                            break;
                        case SDLK_MINUS:
                            viewport.zoom_out();
                            break;
                        case SDLK_s:
                            grid.save_to_file("out.cwy");
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    int cell_x;
                    int cell_y;

                    // TODO don't do this the C way...
                    viewport.screen_coords_to_grid_coords(e.button.x, e.button.y, &cell_x, &cell_y);

                    grid.invert_cell(cell_x, cell_y);
                    break;
                case SDL_MULTIGESTURE:
                    float dDist = e.mgesture.dDist;

                    cout << "pinch " << dDist << endl;
                    viewport.adjust_zoom(dDist * 24);
                    break;
            }
        }

        auto time_before_step = chrono::steady_clock::now();
        grid.step();
        auto time_after_step_before_draw = chrono::steady_clock::now();
//        cout << "Time to step: " <<
//                chrono::duration_cast<chrono::microseconds>(time_after_step_before_draw - time_before_step).count()
//                << "μs" << endl;
        viewport.render_grid(renderer, &grid);
        SDL_UpdateWindowSurface(window);
        auto time_after_draw = chrono::steady_clock::now();
//        cout << "Time to draw: " <<
//                chrono::duration_cast<chrono::microseconds>(time_after_draw - time_after_step_before_draw).count()
//                << "μs" << endl;
    }

    return 0;
}
