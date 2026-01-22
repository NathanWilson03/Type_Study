#define SUCCESS 0
#define FAILURE 1
#define BUFF_SIZE 128
#define G_WIDTH 800
#define G_HEIGHT 600
#define B_WIDTH 250
#define B_HEIGHT 60
#define MAX_SIDES 4
#define MAX_BUTTONS 5
#define SIGNUP_X 350
#define SIGNUP_Y 325
#define LOGIN_X 350
#define LOGIN_Y 225
#define MY_FONT "../fonts/roboto/Roboto-Thin.ttf" 
#define SDL_FLAGS (SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO )
#define WINDOW_FLAGS (SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE ) 


extern int side_count1;
extern int side_count2;
typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *text_surface[4];
    TTF_Font *font[2];
    SDL_Texture *text_texture[4];
    
} Game;

 
const SDL_Point login_shape[] = {
        { 300, 200 },
        { 500, 200},
        { 500, 275},
        { 300, 275 }, 
        { 300, 200 }
    };
  
const SDL_Point signin_shape[] = {
        { 300, 300 },
        { 500, 300},
        { 500, 375},
        { 300, 375 }, 
        { 300, 300 }
    };
       

const char * start_buttons[] = { NULL, "Login", "Signup", "Play as guest" };
