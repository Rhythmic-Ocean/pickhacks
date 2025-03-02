#include "all_thingies.h"

void render_game_screen3(Game *game)
{
    SDL_RenderClear(game->renderer);
    side_grid_generator3(game);
    if (player_rendering(game)) {
        fprintf(stderr, "Error rendering player: %s\n", IMG_GetError());
        game_cleanup(game, EXIT_FAILURE);
    }
    SDL_RenderPresent(game->renderer);
}

void update_game_screen3(Game *game){
    camera_movement(game);
    if (game->sprite_rect.x == 38 && game->sprite_rect.y == 51) { 
        game->state = STATE_YOU_WIN;
    }
}

void side_grid_generator3(Game *game) {
    
    SDL_Rect rect = game->grid_outline_rect;

    int win_width, win_height;
    SDL_GetRendererOutputSize(game->renderer, &win_width, &win_height);


    int tile_width, tile_height;
    SDL_QueryTexture(game->grid_outline, NULL, NULL, &tile_width, &tile_height);

  
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
          
            if (map2[y][x] == 1) {
                rect.x = game->camera.x + x * tile_width;
                rect.y = game->camera.y + y * tile_height;

                SDL_RenderCopy(game->renderer, game->grid_outline, NULL, &rect);
            }
            else if (map2[y][x] == 0) {
                rect.x = game->camera.x + x * tile_width;
                rect.y = game->camera.y + y * tile_height;

                SDL_RenderCopy(game->renderer, game->normal_grid, NULL, &rect);
            }
        }
    }
}