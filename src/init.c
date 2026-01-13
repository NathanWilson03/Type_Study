#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <SDL.h> // use default sdl for now 
#include <SDL_ttf.h>

#include "defs.h"

int open_window(Game *g);
int begin_display(Game *g, char *str);
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
    
    char *str = "Welcome to Type_Study";
    int render_flags, window_color, quit = 0, i = 0;
    SDL_Event e;

    // allows for hardware acceleration
    render_flags = SDL_RENDERER_ACCELERATED;
    // need to initialize to use library   
    if( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }    
    if( TTF_Init() < 0 ) {
        fprintf(stderr, "Could not create text: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    g->window = SDL_CreateWindow("Type_Study", SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED, G_WIDTH, G_HEIGHT, SDL_WINDOW_SHOWN);

    if( !g->window ) {
        fprintf(stderr, "Failed to open window: %s\n", SDL_GetError());
        return 1;
    }

    g->renderer = SDL_CreateRenderer( g->window , -1, 0 );
    if( !g->renderer ) {
        fprintf(stderr, "Failed to create surface: %s\n", SDL_GetError());
        return 1;
    }

        SDL_SetRenderDrawColor(g->renderer, 35, 31, 31, 255);
        while( i < strlen(str) + 1 ) {
        
        begin_display(g, str);
        i++;
        }
        SDL_UpdateWindowSurface( g->window );

        // main game loop
        // everything that happens in this function 
        // stays on the screen 
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

int begin_display(Game *g, char *str) {
    // need to add a fonts dir for portability  
    int i, posX = 10, loaded_char = 1;
    char buff[128];

    strncpy(buff, str, loaded_char);
    buff[loaded_char] = '\0';
    g->font = TTF_OpenFont("/System/Library/Fonts/Monaco.ttf", 30);
    if( !g->font ) {
        fprintf(stderr, "Font init failed: %s\n", TTF_GetError());
        return 1;
    }
    SDL_Color text_color = { 0, 0, 0, 255 }; 

    g->text_surface = TTF_RenderText_Solid(g->font, buff, text_color);
        if( !g->text_surface ) {
            fprintf(stderr, "Text surface failed: %s\n", SDL_GetError());
            return 1;
        }

        g->text_texture = SDL_CreateTextureFromSurface(g->renderer, g->text_surface);

        if( !g->text_texture ) {
            fprintf(stderr, "Text texture failed to render: %s\n", SDL_GetError());
            return 1;
        }
        SDL_Rect text_rect = { 10, 10, g->text_surface->w, g->text_surface->h };
        SDL_RenderCopy(g->renderer, g->text_texture, NULL, &text_rect);

        // shows frame after text 
        // put on
        SDL_RenderPresent(g->renderer);
        loaded_char++;
        SDL_Delay(100);

    return 0;
}

void close_window(Game *g) {

    SDL_FreeSurface( g->text_surface);
    g->text_surface = NULL;

    SDL_DestroyWindow( g->window );
    g->window = NULL;

    SDL_DestroyRenderer( g->renderer );
    g->renderer = NULL;

    SDL_Quit();


}


