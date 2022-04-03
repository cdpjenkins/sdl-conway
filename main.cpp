#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 400;

int main() {
    cout << "Hello World!" << endl;
    int rc = SDL_Init(SDL_INIT_VIDEO);

    if (rc != 0) {
        throw exception();
    }

    SDL_Window *window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if (window == NULL) {
        throw exception();
    }

    cout << "Window open" << endl;

    //Get window surface
    SDL_Surface *screenSurface = SDL_GetWindowSurface( window );

    //Fill the surface white
    SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0x00, 0xFF ) );

    //Update the surface
    SDL_UpdateWindowSurface( window );

    cout << "Rectangle drawn" << endl;

    // Not quite clear why we need to do this
    SDL_Event e;
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                quit = true;
            }
            if (e.type == SDL_KEYDOWN){
                quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN){
                quit = true;
            }
        }
    }

    // //Wait two seconds
    // SDL_Delay( 1000 );

    return 0;
}
