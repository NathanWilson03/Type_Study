#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <SDL.h> // use default sdl for now 

#include "defs.h"

int open_window(Game *g);
void close_window(Game *g);


int main() {

    Game g = {0};
    if( open_window(&g) ) {
        return 1;
    }

    close_window(&g);

    return 0;

}

int open_window(Game *g) {

    int render_flags, window_color, quit = 0;
    SDL_Event e;

    // allows for hardware acceleration
    render_flags = SDL_RENDERER_ACCELERATED;
    // need to initialize to use library   
    if( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    g->window = SDL_CreateWindow("Type_Study", SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED, G_WIDTH, G_HEIGHT, SDL_WINDOW_SHOWN);

    if( !g->window ) {
        fprintf(stderr, "Failed to open window: %s\n", SDL_GetError());
        return 1;
    }
    // getting the surface allows to draw
    // maybe could use renderer as well
    g->surface = SDL_GetWindowSurface( g->window );
    if( !g->surface ) {
        fprintf(stderr, "Failed to create surface: %s\n", SDL_GetError());
        return 1;
    }

    // for window color param in fill rect func 
    window_color = SDL_MapRGB(g->surface->format, 0x21, 0x21, 0x21);

    SDL_FillRect( g->surface, NULL, window_color );
    SDL_UpdateWindowSurface( g->window );

    // main game loop
    while( quit == 0 ) {
        while( SDL_PollEvent(&e) ) {
            if( e.type  == SDL_QUIT ) {
                // will not return until quit is entered
                quit = 1;
            }
        }
    }
    return 0;
}

void close_window(Game *g) {

    SDL_FreeSurface( g->surface );
    g->surface = NULL;

    SDL_DestroyWindow( g->window );
    g->window = NULL;

    SDL_Quit();


}


