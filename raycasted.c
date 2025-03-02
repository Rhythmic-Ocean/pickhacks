// raycasted.c
#include "all_thingies.h"

// Rename rayloop to render_raycast (or keep as rayloop if preferred)
void render_raycast(Game *game) {  // No while(1)
    SDL_SetRenderDrawColor(game->renderer, 50, 50, 50, 255);
    SDL_RenderClear(game->renderer);

    for (int x = 0; x < SCREEN_WIDTH; x++) {
        float ray_angle = game->player_angle - game->fov / 2 + (game->fov * x / (float)SCREEN_WIDTH);
        float ray_x = game->player_x;
        float ray_y = game->player_y;
        float dx = cosf(ray_angle);
        float dy = sinf(ray_angle);
        float distance = 0.0f;

        while (distance < 20.0f) {
            ray_x += dx * 0.05f;
            ray_y += dy * 0.05f;
            int map_x = (int)ray_x;
            int map_y = (int)ray_y;
            if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT) break;
            if (game->current_map[map_y][map_x] == 1) break;  // Use current_map
            distance += 0.05f;
        }

        float corrected_distance = distance * cosf(ray_angle - game->player_angle);
        int wall_height = (int)(SCREEN_HEIGHT / (corrected_distance + 0.1f));
        if (wall_height > SCREEN_HEIGHT) wall_height = SCREEN_HEIGHT;

        SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);
        SDL_RenderDrawLine(game->renderer, x, 0, x, SCREEN_HEIGHT / 2 - wall_height / 2);

        int tex_x = (int)((ray_x - (int)ray_x) * TEX_WIDTH) % TEX_WIDTH;
        SDL_Rect wall_src = {tex_x, 0, 1, TEX_HEIGHT};
        SDL_Rect wall_dst = {x, SCREEN_HEIGHT / 2 - wall_height / 2, 2, wall_height};
        SDL_RenderCopy(game->renderer, game->wall_texture, &wall_src, &wall_dst);

        SDL_SetRenderDrawColor(game->renderer, 139, 69, 19, 255);
        SDL_RenderDrawLine(game->renderer, x, SCREEN_HEIGHT / 2 + wall_height / 2, x, SCREEN_HEIGHT);
    }

    SDL_RenderPresent(game->renderer);
}

void input_handling_3d(Game *game) {
    float move_speed = 0.1f;
    float rot_speed = 0.05f;

    float dx = cosf(game->player_angle) * move_speed;
    float dy = sinf(game->player_angle) * move_speed;

    if (game->keyboard_state[SDL_SCANCODE_W] || game->keyboard_state[SDL_SCANCODE_UP]) {
        float new_x = game->player_x + dx;
        float new_y = game->player_y + dy;
        if (new_x >= 0 && new_x < MAP_WIDTH && new_y >= 0 && new_y < MAP_HEIGHT && game->current_map[(int)new_y][(int)new_x] == 0) {
            game->player_x = new_x;
            game->player_y = new_y;
            game->sprite_rect.x = (int)new_x;  // Sync 2D position
            game->sprite_rect.y = (int)new_y;
        }
    }
    if (game->keyboard_state[SDL_SCANCODE_S] || game->keyboard_state[SDL_SCANCODE_DOWN]) {
        float new_x = game->player_x - dx;
        float new_y = game->player_y - dy;
        if (new_x >= 0 && new_x < MAP_WIDTH && new_y >= 0 && new_y < MAP_HEIGHT && game->current_map[(int)new_y][(int)new_x] == 0) {
            game->player_x = new_x;
            game->player_y = new_y;
            game->sprite_rect.x = (int)new_x;  // Sync 2D position
            game->sprite_rect.y = (int)new_y;
        }
    }
    if (game->keyboard_state[SDL_SCANCODE_A] || game->keyboard_state[SDL_SCANCODE_LEFT]) {
        game->player_angle -= rot_speed;
    }
    if (game->keyboard_state[SDL_SCANCODE_D] || game->keyboard_state[SDL_SCANCODE_RIGHT]) {
        game->player_angle += rot_speed;
    }

    if (game->player_angle < 0) game->player_angle += 2 * PI;
    if (game->player_angle >= 2 * PI) game->player_angle -= 2 * PI;
}

void update_game_screen4(Game *game) {
    // No need for camera_movement—it’s 2D, replaced by input_handling_3d
    if (game->sprite_rect.x == 57 && game->sprite_rect.y == 20) {
        Mix_PlayChannel(-1, game->winning_sound, 0);
        game->state = STATE_YOU_WIN;
    }
}