#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>  
#include <stdbool.h>
#include<SDL2/SDL_mixer.h>

typedef enum{
    STATE_TITLE,
    STATE_MAZE1,
    STATE_YOU_WIN,
} GameState;

#define TITLE "Game"
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1280
#define IMAGE_FLAG (IMG_INIT_JPG | IMG_INIT_PNG)
#define MAP_WIDTH 100
#define MAP_HEIGHT 100
#define MIXER_FLAGX MIX_INIT_OGG
int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0 ,0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0,1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0,1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    /*{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1},
    {1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1}, // THESE ARE OTHER MAPS WIP!!!!
    {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}*/
    /*{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1},
    {1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1},
    {1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},*/



};



typedef struct{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *grid_outline;
    SDL_Rect grid_outline_rect;
    SDL_Rect camera;
    const Uint8 *keyboard_state;
    SDL_Texture *sprite_back;
    SDL_Texture *sprite_left;
    SDL_Texture *sprite_right;
    SDL_Texture *sprite_front;
    SDL_Rect sprite_rect;
    SDL_Texture *normal_grid;
    SDL_Texture *title_screen;
    SDL_Texture *you_win_screen;
    Uint32 start_time;
    TTF_Font *font;
    SDL_Texture *timer_texture;
    SDL_Rect timer_rect;
    GameState state;
    Mix_Music *music;
}Game;

bool sdl_initialize(Game *game);
bool load_media (Game *game);
void game_cleanup(Game *game, int exit_status);
void side_grid_generator(Game *game);
void camera_movement(Game *game);
bool player_rendering(Game *game);
void render_title_screen(Game *game);
void update_title_screen(Game *game);
void render_game_screen(Game *game);
void update_game_screen(Game *game);
void render_you_win_screen(Game *game);
void update_you_win_screen(Game *game);

int main(void) {
    Game game = {
        .window = NULL,
        .renderer = NULL,
        .grid_outline = NULL,
        .grid_outline_rect = {0, 0, 0, 0},
        .camera = {0, 0, 0, 0},
        .keyboard_state = SDL_GetKeyboardState(NULL),
        .sprite_back = NULL,
        .sprite_front = NULL,
        .sprite_right = NULL,
        .sprite_left = NULL,
        .sprite_rect = {1, 2, 0, 0},
        .normal_grid = NULL,
        .state = STATE_TITLE,  // Initial state
        .title_screen = NULL,
        .you_win_screen = NULL,
    };

    if (sdl_initialize(&game)) {
        printf("Very Bad\n");
        game_cleanup(&game, EXIT_FAILURE);
    }
    if (load_media(&game)) {
        printf("Just Bad\n");
        game_cleanup(&game, EXIT_FAILURE);
    }
    if(Mix_PlayMusic(game.music, -1)){
        printf("All bad\n");
        game_cleanup(&game, EXIT_FAILURE);
    }
    while (1) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                game_cleanup(&game, EXIT_SUCCESS);
            }
        }

        switch (game.state) {
            case STATE_TITLE:
                update_title_screen(&game);
                render_title_screen(&game);
                break;
            case STATE_MAZE1:
                update_game_screen(&game);
                render_game_screen(&game);
                break;
            case STATE_YOU_WIN:
                update_you_win_screen(&game);
                render_you_win_screen(&game);
                break;
            default:
                break;
        }

        SDL_Delay(100);  
    }

    return 0; 
}
void game_cleanup(Game *game, int exit_status){
    Mix_HaltMusic();
    Mix_FreeMusic(game->music);
    SDL_DestroyTexture(game->timer_texture);
    TTF_CloseFont(game->font);
    SDL_DestroyTexture(game->title_screen);
    SDL_DestroyTexture(game->title_screen);
    SDL_DestroyTexture(game->sprite_right);
    SDL_DestroyTexture(game->sprite_left);
    SDL_DestroyTexture(game->sprite_front);
    SDL_DestroyTexture(game->sprite_back);
    SDL_DestroyTexture(game->normal_grid);
    SDL_DestroyTexture(game->grid_outline);
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    exit(exit_status);
}

bool sdl_initialize(Game *game){
    if(SDL_Init(SDL_INIT_EVERYTHING))
    {
        fprintf(stderr,"Error initializing SDL: %s\n", SDL_GetError());
        return true;
    }
    int image_init = IMG_Init(IMAGE_FLAG);
    if((image_init & IMAGE_FLAG) != IMAGE_FLAG){
        fprintf(stderr, "Error initializing images %s\n", SDL_GetError());
        return true;
    }
    if(TTF_Init())
    {
        fprintf(stderr, "Error initializing SDL_ttf: %s\n", IMG_GetError());
        return true;
    }
    game->window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(!game->window)
    {
        fprintf(stderr, "Error initializing window: %s\n", SDL_GetError());
        return true;
    }
    game->renderer = SDL_CreateRenderer(game->window, -1, 0);
    if(!game->renderer)
    {
        fprintf(stderr, "Error initializing renderer: %s\n", SDL_GetError());
        return true;
    }
    int mix_init = Mix_Init(MIXER_FLAGX);
    if((mix_init & MIXER_FLAGX) != MIXER_FLAGX){
        fprintf(stderr, "Error rendering sound effects: %s\n", Mix_GetError());
        return true;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {  // Add this
        fprintf(stderr, "Error opening audio: %s\n", Mix_GetError());
        return true;
    }
    game->state = STATE_TITLE;
    return false;
}

bool load_media(Game *game){
    game->grid_outline = IMG_LoadTexture(game->renderer, "images/grid_outline.png");
    if(!game->grid_outline)
    {
        fprintf(stderr, "Error loading outer grid textures %s\n", IMG_GetError());
        return true;
    }
    if(SDL_QueryTexture(game->grid_outline, NULL, NULL, &game->grid_outline_rect.w, &game->grid_outline_rect.h)){
        fprintf(stderr, "Error rendering grid outline: %s\n", IMG_GetError());
        return true;
    }
    game->sprite_back = IMG_LoadTexture(game->renderer, "images/sprit_back.png");
    if(!game->sprite_back)
    {
        fprintf(stderr, "Error loading player's back texture: %s\n", IMG_GetError());
        return true;
    }
    game->title_screen = IMG_LoadTexture(game->renderer, "images/Start.jpeg");
    if(!game->title_screen)
    {
        fprintf(stderr, "Error rendering timer: %s\n", IMG_GetError());
        return true;
    }
    game->you_win_screen = IMG_LoadTexture(game->renderer, "images/You_win.jpeg");
    if (!game->you_win_screen) {
        fprintf(stderr, "Error loading game over screen texture: %s\n", IMG_GetError());
        return true;
    }
    if(SDL_QueryTexture(game->sprite_back, NULL, NULL, &game->sprite_rect.w, &game->sprite_rect.h)){
        fprintf(stderr, "Error rendering grid outline: %s\n", IMG_GetError());
        return true;
    }
    game->sprite_front = IMG_LoadTexture(game->renderer, "images/sprit_front.png");
    if(!game->sprite_front)
    {
        fprintf(stderr, "Error loading player's front texture: %s\n", IMG_GetError());
        return true;
    }
    game->sprite_left = IMG_LoadTexture(game->renderer, "images/sprit_left.png");
    if(!game->sprite_left)
    {
        fprintf(stderr, "Error loading player's left texture: %s\n", IMG_GetError());
        return true;
    }
    game->sprite_right = IMG_LoadTexture(game->renderer, "images/sprit_right.png");
    if(!game->sprite_right)
    {
        fprintf(stderr, "Error loading player's right texture: %s\n", IMG_GetError());
        return true;
    }
    game->sprite_rect.w *=2;
    game->sprite_rect.h *=2;
    game->normal_grid = IMG_LoadTexture(game->renderer, "images/Selection_075.png");
    if(!game->normal_grid)
    {
        fprintf(stderr, "Error loading player's normal grid texture: %s\n", IMG_GetError());
        return true;
    }
    game->music = Mix_LoadMUS("music/freesoftwaresong-8bit.ogg");
    if(!game->music){
        fprintf(stderr, "Error loading music: %s\n",  Mix_GetError());
        return true;
    }
    return false;
    return false;
}  
void side_grid_generator(Game *game) {
    
    SDL_Rect rect = game->grid_outline_rect;

    int win_width, win_height;
    SDL_GetRendererOutputSize(game->renderer, &win_width, &win_height);


    int tile_width, tile_height;
    SDL_QueryTexture(game->grid_outline, NULL, NULL, &tile_width, &tile_height);

  
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
          
            if (map[y][x] == 1) {
                rect.x = game->camera.x + x * tile_width;
                rect.y = game->camera.y + y * tile_height;

                SDL_RenderCopy(game->renderer, game->grid_outline, NULL, &rect);
            }
            else if (map[y][x] == 0) {
                rect.x = game->camera.x + x * tile_width;
                rect.y = game->camera.y + y * tile_height;

                SDL_RenderCopy(game->renderer, game->normal_grid, NULL, &rect);
            }
        }
    }
}

void camera_movement(Game *game) {
    int speed = 1;

    
    int new_x = game->sprite_rect.x;
    int new_y = game->sprite_rect.y;

 
    if (game->keyboard_state[SDL_SCANCODE_UP] || game->keyboard_state[SDL_SCANCODE_W]) {
        new_y -= 1; 
    }
    if (game->keyboard_state[SDL_SCANCODE_DOWN] || game->keyboard_state[SDL_SCANCODE_S]) {
        new_y += 1; 
    }
    if (game->keyboard_state[SDL_SCANCODE_RIGHT] || game->keyboard_state[SDL_SCANCODE_D]) {
        new_x += 1; 
    }
    if (game->keyboard_state[SDL_SCANCODE_LEFT] || game->keyboard_state[SDL_SCANCODE_A]) {
        new_x -= 1; 
    }

    
    if (new_x >= 0 && new_x < MAP_WIDTH && new_y >= 0 && new_y < MAP_HEIGHT && map[new_y][new_x] == 0) {
        game->sprite_rect.x = new_x;
        game->sprite_rect.y = new_y;
    }

    int tile_width = game->grid_outline_rect.w;
    int tile_height = game->grid_outline_rect.h;
    game->camera.x = (SCREEN_WIDTH / 2) - (game->sprite_rect.x * tile_width) - (game->grid_outline_rect.w / 2);
    game->camera.y = (SCREEN_HEIGHT / 2) - (game->sprite_rect.y * tile_height) - (game->grid_outline_rect.w / 2);
}

bool player_rendering(Game *game) {
    SDL_Rect render_rect = {
        SCREEN_WIDTH / 2 - game->grid_outline_rect.w / 2,
        SCREEN_HEIGHT / 2 - game->grid_outline_rect.w / 2,
        game->grid_outline_rect.w,
        game->grid_outline_rect.h
    };

    if (game->keyboard_state[SDL_SCANCODE_UP] || game->keyboard_state[SDL_SCANCODE_W]) {
        return SDL_RenderCopy(game->renderer, game->sprite_back, NULL, &render_rect) != 0;
    }
    else if (game->keyboard_state[SDL_SCANCODE_DOWN] || game->keyboard_state[SDL_SCANCODE_S]) {
        return SDL_RenderCopy(game->renderer, game->sprite_front, NULL, &render_rect) != 0;
    }
    else if (game->keyboard_state[SDL_SCANCODE_RIGHT] || game->keyboard_state[SDL_SCANCODE_D]) {
        return SDL_RenderCopy(game->renderer, game->sprite_right, NULL, &render_rect) != 0;
    }
    else if (game->keyboard_state[SDL_SCANCODE_LEFT] || game->keyboard_state[SDL_SCANCODE_A]) {
        return SDL_RenderCopy(game->renderer, game->sprite_left, NULL, &render_rect) != 0;
    }
    else {
        return SDL_RenderCopy(game->renderer, game->sprite_front, NULL, &render_rect) != 0;
    }
}

void render_title_screen(Game *game) {
    SDL_RenderClear(game->renderer);
    SDL_Rect dest = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(game->renderer, game->title_screen, NULL, &dest);
    SDL_RenderPresent(game->renderer);
}

void update_title_screen(Game *game) {
    if (game->keyboard_state[SDL_SCANCODE_SPACE]) {
        game->state = STATE_MAZE1;  
    }
}
void render_game_screen(Game *game) {
    SDL_RenderClear(game->renderer);
    side_grid_generator(game);
    if (player_rendering(game)) {
        fprintf(stderr, "Error rendering player: %s\n", IMG_GetError());
        game_cleanup(game, EXIT_FAILURE);
    }
    SDL_RenderPresent(game->renderer);
}
void update_game_screen(Game *game) {
    camera_movement(game);
    
    if (game->sprite_rect.x == 57 && game->sprite_rect.y == 20) {
        game->state = STATE_YOU_WIN;
    }
}
void render_you_win_screen(Game *game) {
    SDL_RenderClear(game->renderer);
    SDL_Rect dest = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(game->renderer, game->you_win_screen, NULL, NULL);
    SDL_RenderPresent(game->renderer);
}
void update_you_win_screen(Game *game) {
    if (game->keyboard_state[SDL_SCANCODE_SPACE]) {
        game->state = STATE_TITLE; 
        game->sprite_rect.x = 1;
        game->sprite_rect.y = 2;
    }
}
