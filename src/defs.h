#define SUCCESS 0
#define FAILURE 1
#define BUFF_SIZE 128
#define G_WIDTH 800
#define G_HEIGHT 600
#define B_WIDTH 250
#define B_HEIGHT 60
#define MY_FONT "../fonts/roboto/Roboto-Regular.ttf" 
#define SDL_FLAGS (SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO )
#define WINDOW_FLAGS (SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE ) 

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *text_surface;
    TTF_Font *font;
    SDL_Texture *text_texture;
    
} Game;

typedef struct {

    SDL_Renderer *renderer;

} Button;



