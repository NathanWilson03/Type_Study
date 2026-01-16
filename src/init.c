#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <SDL.h> // use default sdl for now 
#include <SDL_ttf.h>

#include "defs.h"
static int loaded_char_str1 = 1; 
static int loaded_char_str2 = 1;
int init_fields(Game *g);
int open_window(Game *g);
int begin_display(Game *g, const char *str);
void close_window(Game *g);


int main() {

    Game g = {0};
    if( open_window(&g) ) {
        return 1;
    }

    close_window(&g);

    return 0;

}

int init_fields(Game *g) {
    int render_flags = SDL_RENDERER_ACCELERATED;
   
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

    g->renderer = SDL_CreateRenderer( g->window , -1, render_flags );
    if( !g->renderer ) {
        fprintf(stderr, "Failed to create surface: %s\n", SDL_GetError());
        return 1;
    }


    g->font = TTF_OpenFont("/System/Library/Fonts/Monaco.ttf", 30);
    if( !g->font ) {
        fprintf(stderr, "Font init failed: %s\n", TTF_GetError());
        return 1;
    }
    return 0;
}




int open_window(Game *g) {

    const char *welcome_str = "Welcome to Type_Study. ";
    const char *info_str = "Please enter your User Name.";
    int window_color, quit = 0, i = 0;
    SDL_Event e;

    init_fields(g);

    // need to initialize to use library   
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
    SDL_SetRenderDrawColor(g->renderer, 35, 31, 31, 255);
    SDL_RenderClear(g->renderer);
    
    begin_display(g, welcome_str);
    SDL_RenderPresent(g->renderer);
    }
    return 0;
}

int get_user_info(Game *g) {
    return 0;
}



int begin_display(Game *g, const char *str) {
    // need to add a fonts dir for portability  
    int i, posY = 10, flag = 0;

    char buff[128];
    const char *str2 = "Please enter your username";
    if( loaded_char_str1 > strlen(str) ) {
        str = str2;
        posY = 50;
        strncpy(buff, str, loaded_char_str2);
        buff[loaded_char_str2] = '\0';
        loaded_char_str2++;
    } else {

    strncpy(buff, str, loaded_char_str1);
    buff[loaded_char_str1] = '\0';
    loaded_char_str1++;
    }

    SDL_RenderClear(g->renderer);
    SDL_Color text_color = { 255, 255, 255, 255 }; 

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
    SDL_Rect text_rect = { 10, posY, g->text_surface->w, g->text_surface->h };
    SDL_RenderCopy(g->renderer, g->text_texture, NULL, &text_rect);

    // shows frame after text 
    // put on
    SDL_RenderPresent(g->renderer);
    SDL_Delay(100);
    // free the surface created 
    SDL_FreeSurface(g->text_surface);
    SDL_DestroyTexture(g->text_texture);

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


