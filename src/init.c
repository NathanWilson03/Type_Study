#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
/* default sdl library for now */
#include <SDL.h>
#include <SDL_ttf.h>
#include "defs.h"

/* could add audio later */

int open_window(Game *);
int close_window(Game *);
int start_game(Game *, int *, int *); 

int main() {
        
    Game *g = malloc( sizeof(Game) );
    open_window(g);

    close_window(g);

    return 0;
}

int open_window(Game *g) {
    
    int quit = 0, num_chr_disp1 = 1, num_chr_disp2 = 1;  
    SDL_Event e;

    /* allow for window functionality */
    if( SDL_Init(SDL_FLAGS) != 0) {
        fprintf(stderr, "Window failed to init: %s\n", SDL_GetError());
        return FAILURE;
    }
    if( TTF_Init() != 0 ) {
        fprintf(stderr, "Text failed to init: %s\n", SDL_GetError());
        return FAILURE;
    }

    g->window = SDL_CreateWindow("Type_Study", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                 G_WIDTH, G_HEIGHT, WINDOW_FLAGS);
    if( !g->window ) {
        fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
        return FAILURE;
    }

    g->renderer =  SDL_CreateRenderer(g->window, -1, SDL_RENDERER_ACCELERATED);


    if( !g->renderer) {
        fprintf(stderr, "Renderer failed to begin display: %s\n", SDL_GetError());
        return FAILURE;
    }
    /* change to be compatable with more fonts */
    g->font = TTF_OpenFont( MY_FONT, 48 );

    if( !g->font ) {
        fprintf(stderr, "TTF Font failed to init: %s\n", TTF_GetError());
        return FAILURE;
    }
   


    while( quit == 0 ) {
        while( SDL_PollEvent(&e) ) {
            if( e.type == SDL_QUIT ) {
                quit = 1;
            }
        }
    SDL_SetRenderDrawColor( g->renderer, 0, 0, 0, 0 );
    SDL_RenderClear(g->renderer);

    start_game(g, &num_chr_disp1, &num_chr_disp2);

    SDL_RenderPresent(g->renderer);
    
    /* freeing after presenting */
    SDL_FreeSurface(g->text_surface);
    g->text_surface = NULL;

    SDL_DestroyTexture(g->text_texture);
    g->text_texture = NULL;
    


    }

   return SUCCESS;
}

int start_game( Game *g, int *num_chr_disp1, int *num_chr_disp2) {
    
    char *welcome_str1 = "Welcome to Type_Study.";
    char *welcome_str2 = "Please";
    char buff[BUFF_SIZE];
    int pos_x, pos_y;
    SDL_Color text_color = { 255 ,255 ,255 ,255 }; /* black */

    /* initial prompt has typing effect */
    if( *num_chr_disp1 < strlen(welcome_str1) ) {
        
        buff[*num_chr_disp1] = '\0';
        strncpy(buff, welcome_str1, *num_chr_disp1);
        pos_x = 150;
        pos_y = 50;
        (*num_chr_disp1)++;
    
    } else {

        if( *num_chr_disp1 == strlen(welcome_str1) ){
            SDL_Delay(200);
            (*num_chr_disp1)++;
        }

        buff[*num_chr_disp2] = '\0';
        strncpy(buff, welcome_str2, *num_chr_disp2);
        pos_x = 300;
        pos_y = 100;

        if( *num_chr_disp2 < strlen(welcome_str2) ) {
        (*num_chr_disp2)++;
        }
    }



 
    /* stored in CPU */ 
    g->text_surface = TTF_RenderText_Solid( g->font, buff, text_color );
    if( !g->text_surface ) {
        fprintf(stderr, "Text Surface failed to init: %s\n", TTF_GetError());
        return FAILURE;
    }

    g->text_texture = SDL_CreateTextureFromSurface(g->renderer, g->text_surface);
    if( !g->text_texture ) {
        fprintf(stderr, "Text Texture failed to init: %s\n", TTF_GetError());
        return FAILURE;
    }

    SDL_Rect text_rect = { pos_x, pos_y, g->text_surface->w, g->text_surface->h };
    SDL_RenderCopy(g->renderer, g->text_texture, NULL, &text_rect);
    
    if( *num_chr_disp2 <= strlen(welcome_str2) ) { 
    SDL_Delay(100);
    }

    if( *num_chr_disp2 >= strlen(welcome_str2) ) {
    /* make the buttons for login signup */
    SDL_Rect b_rect = { ( G_WIDTH - B_WIDTH ) / 2, 200, B_WIDTH, B_HEIGHT };
    SDL_SetRenderDrawColor(g->renderer, 200, 200, 200, 255);
    SDL_RenderFillRect(g->renderer, &b_rect);


    }


    
    
    
    return SUCCESS;
}








int close_window(Game *g) {
     
    SDL_DestroyWindow(g->window);
    g->window = NULL;
    SDL_DestroyRenderer(g->renderer);
    g->renderer = NULL;
    SDL_Quit();

    free(g);
    g = NULL;

    return SUCCESS;

}
 






