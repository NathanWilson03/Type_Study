#define G_WIDTH 800
#define G_HEIGHT 600
#define MY_FONT "fonts/Roboto-Regular.ttf" 

typedef struct {
    SDL_Window *window;
    SDL_Surface *text_surface;
    SDL_Renderer *renderer;
    TTF_Font *font;
    SDL_Texture *text_texture;
} Game;


