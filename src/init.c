#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
/* default sdl library for now */
#include <SDL.h>
#include <SDL_ttf.h>
#include "defs.h"

/* could add audio later */





/* FIGURE OUT BUTTON EVENTS AND GET GAME STARTED */
int open_window(Game *);
int close_window(Game *);
int start_game(Game *, int *, int *); 
int make_buttons(Game *, const SDL_Point[], int, int); 
int side_count1 = 0;
int side_count2 = 0;


/* static variables for cool effects */

int main() {
        
    /* could put this in a set up func later */
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
    g->font[0] = TTF_OpenFont( MY_FONT, 48 );
    g->font[1] = TTF_OpenFont( MY_FONT, 38 );


    if( !g->font[0] || !g->font[1] ) {
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

    if( start_game(g, &num_chr_disp1, &num_chr_disp2) ) {
        return FAILURE;
    }
    SDL_RenderPresent(g->renderer);
    
    /* freeing after presenting */
    SDL_FreeSurface(g->text_surface[0]);
    g->text_surface[0] = NULL;

    SDL_DestroyTexture(g->text_texture[0]);
    g->text_texture[0] = NULL;
    


    }

   return SUCCESS;
}
/* make sure we free correctly */
int start_game( Game *g, int *num_chr_disp1, int *num_chr_disp2 ) {
    
    char *welcome_str1 = "Welcome to Type_Study.";
    char *welcome_str2 = "Please";
    char buff[BUFF_SIZE]; /* used for type effect */
    int pos_x, pos_y; /* positions for text */
    SDL_Color text_color = { 255 ,255 ,255 ,255 }; /* white */

    /* initial prompt has typing effect */
    if( *num_chr_disp1 < strlen(welcome_str1) ) {
        
        buff[*num_chr_disp1] = '\0';
        strncpy(buff, welcome_str1, *num_chr_disp1);
        pos_x = 150;
        pos_y = 50;
        (*num_chr_disp1)++;
    
    } else {

        if( *num_chr_disp1 == strlen(welcome_str1) ){
            SDL_Delay(200); /* give a second to read */
            (*num_chr_disp1)++;
        }

        buff[*num_chr_disp2] = '\0';
        strncpy(buff, welcome_str2, *num_chr_disp2);
        pos_x = 320;
        pos_y = 100;

        if( *num_chr_disp2 < strlen(welcome_str2) ) {
        (*num_chr_disp2)++;
        }
    }


       g->text_surface[0] = TTF_RenderText_Solid( g->font[0], buff, text_color );



    if( !g->text_surface[0] ) {
        fprintf(stderr, "Text Surface failed to init: %s\n", TTF_GetError());
        return FAILURE;
    }

    g->text_texture[0] = SDL_CreateTextureFromSurface(g->renderer, g->text_surface[0]);
    if( !g->text_texture[0] ) {
        fprintf(stderr, "Text Texture failed to init: %s\n", TTF_GetError());
        return FAILURE;
 
    }
    /* create login and sign in buttons */
    if( *num_chr_disp2 >= strlen(welcome_str2) ) {

        
        if ( make_buttons(g, login_shape, 0, side_count1) ) {
            return FAILURE;
        }
        if( side_count1 <= MAX_SIDES ) 
        side_count1++;

        if( side_count1 > MAX_SIDES ) {
            if ( make_buttons(g, signin_shape, 1, side_count2)) {
                return FAILURE;
            }

            if( side_count2 <= MAX_SIDES ) 
                side_count2++;
        }
    }
        


    SDL_Rect text_rect = { pos_x, pos_y, g->text_surface[0]->w, g->text_surface[0]->h };
    SDL_RenderCopy(g->renderer, g->text_texture[0], NULL, &text_rect);
    
    if( *num_chr_disp2 <= strlen(welcome_str2) ) { 
    SDL_Delay(100);
    }


    
    return SUCCESS;
}
/* need to center font and handle the memory by freeing */
int make_buttons(Game *g, const SDL_Point shape[], int btn_id, int side_count) {

    /* for now the draw color for buttons all white */
    int text_x, text_y;

    if( !btn_id ) {
        text_x = 340; text_y = 205;
    } else {
        text_x = 335; text_y = 305;
    }



    SDL_Color text_color = { 255 ,255 ,255 ,255 }; /* white */
    SDL_SetRenderDrawColor(g->renderer, 255, 255, 255, 255);
    SDL_Delay(100);
    btn_id++;
    
    SDL_RenderDrawLines(g->renderer, shape, side_count);
    g->text_surface[btn_id] = TTF_RenderText_Solid( g->font[1], start_buttons[btn_id], text_color );
    if( !g->text_surface[btn_id] ) {
        fprintf(stderr, "Text Surface failed to init: %s\n", TTF_GetError());
        return FAILURE;
    }
    
    g->text_texture[btn_id] = SDL_CreateTextureFromSurface(g->renderer, g->text_surface[btn_id]); 
    if( !g->text_texture[btn_id] ) {
        fprintf(stderr, "Text Texture failed to init: %s\n", TTF_GetError());
        return FAILURE;
    }

    SDL_Rect text_rect = { text_x, text_y, g->text_surface[btn_id]->w, g->text_surface[btn_id]->h };
    SDL_RenderCopy(g->renderer, g->text_texture[btn_id], NULL, &text_rect);
 


    

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
