#ifndef MAIN_H  
#define MAIN_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>  
#include <stdbool.h>
#include<SDL2/SDL_mixer.h>

#define TITLE "MAZE"
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1280
#define IMAGE_FLAG (IMG_INIT_JPG | IMG_INIT_PNG)
#define MAP_WIDTH 100
#define MAP_HEIGHT 100
#define MIXER_FLAGX MIX_INIT_OGG 
#define PI 3.14159f

typedef enum{
    STATE_TITLE,
    STATE_MAZE1,
    STATE_MAZE2,
    STATE_MAZE3,
    STATE_YOU_WIN,
} GameState;


extern int map[MAP_HEIGHT][MAP_WIDTH];
extern int map1[MAP_HEIGHT][MAP_WIDTH];
extern int map2[MAP_HEIGHT][MAP_WIDTH];

typedef struct {
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
    int (*current_map)[MAP_WIDTH];
    Mix_Chunk *winning_sound;
} Game;

bool sdl_initialize(Game *game);
bool load_media (Game *game);
void game_cleanup(Game *game, int exit_status);
void side_grid_generator(Game *game);
void side_grid_generator2(Game *game);
void camera_movement(Game *game);
bool player_rendering(Game *game);
void render_title_screen(Game *game);
void update_title_screen(Game *game);
void render_game_screen(Game *game);
void update_game_screen(Game *game);
void render_you_win_screen(Game *game);
void update_you_win_screen(Game *game);
void render_game_screen2(Game *game);
void update_game_screen2(Game *game);
void render_game_screen3(Game *game);
void update_game_screen3(Game *game);
void side_grid_generator3(Game *game);

#endif