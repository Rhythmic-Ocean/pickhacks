#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>

#define SCREEN_WIDTH 800   // Smaller for simplicity, adjust as needed
#define SCREEN_HEIGHT 600
#define MAP_WIDTH 100
#define MAP_HEIGHT 100
#define PI 3.14159f

// Your Maze 1 map (simplified to 24x24 for this example, expand as needed)
int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// Game structure
typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    const Uint8 *keyboard_state;
    float player_x;      // Player X position (float for smooth movement)
    float player_y;      // Player Y position
    float player_angle;  // Player facing direction (radians)
    float fov;           // Field of view (radians)
    bool running;        // Game loop control
} Game;

// Initialize SDL and game state
bool init_game(Game *game) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Init failed: %s\n", SDL_GetError());
        return false;
    }

    game->window = SDL_CreateWindow("Raycasting Demo",
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   SCREEN_WIDTH, SCREEN_HEIGHT,
                                   0);
    if (!game->window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return false;
    }

    game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);
    if (!game->renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        return false;
    }

    game->keyboard_state = SDL_GetKeyboardState(NULL);
    game->player_x = 2.0f;       // Start at (2, 2)
    game->player_y = 2.0f;
    game->player_angle = 0.0f;   // Facing right
    game->fov = PI / 3.0f;       // 60 degrees FOV
    game->running = true;

    return true;
}

// Clean up resources
void cleanup(Game *game) {
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
}

// Handle player movement and rotation
void handle_input(Game *game) {
    float move_speed = 0.1f;   // Move 0.1 units per frame
    float rot_speed = 0.05f;   // Rotate 0.05 radians per frame

    float dx = cosf(game->player_angle) * move_speed;
    float dy = sinf(game->player_angle) * move_speed;

    if (game->keyboard_state[SDL_SCANCODE_W]) {
        float new_x = game->player_x + dx;
        float new_y = game->player_y + dy;
        if (map[(int)new_y][(int)new_x] == 0) {  // Collision check
            game->player_x = new_x;
            game->player_y = new_y;
        }
    }
    if (game->keyboard_state[SDL_SCANCODE_S]) {
        float new_x = game->player_x - dx;
        float new_y = game->player_y - dy;
        if (map[(int)new_y][(int)new_x] == 0) {
            game->player_x = new_x;
            game->player_y = new_y;
        }
    }
    if (game->keyboard_state[SDL_SCANCODE_A]) {
        game->player_angle -= rot_speed;  // Rotate left
    }
    if (game->keyboard_state[SDL_SCANCODE_D]) {
        game->player_angle += rot_speed;  // Rotate right
    }

    // Keep angle in [0, 2π)
    if (game->player_angle < 0) game->player_angle += 2 * PI;
    if (game->player_angle >= 2 * PI) game->player_angle -= 2 * PI;
}

// Raycasting rendering
void raycast(Game *game) {
    // Clear screen to dark gray
    SDL_SetRenderDrawColor(game->renderer, 50, 50, 50, 255);
    SDL_RenderClear(game->renderer);

    for (int x = 0; x < SCREEN_WIDTH; x++) {
        // Calculate ray angle
        float ray_angle = game->player_angle - game->fov / 2 + (game->fov * x / (float)SCREEN_WIDTH);
        float ray_x = game->player_x;
        float ray_y = game->player_y;
        float dx = cosf(ray_angle);
        float dy = sinf(ray_angle);
        float distance = 0.0f;

        // Step ray until wall hit
        while (distance < 20.0f) {
            ray_x += dx * 0.1f;
            ray_y += dy * 0.1f;
            int map_x = (int)ray_x;
            int map_y = (int)ray_y;
            if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT) break;
            if (map[map_y][map_x] == 1) break;
            distance += 0.1f;
        }

        // Correct distance for fisheye effect
        float corrected_distance = distance * cosf(ray_angle - game->player_angle);
        int wall_height = (int)(SCREEN_HEIGHT / (corrected_distance + 0.1f));  // Avoid division by zero
        if (wall_height > SCREEN_HEIGHT) wall_height = SCREEN_HEIGHT;

        // Draw ceiling (blue)
        SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);
        SDL_RenderDrawLine(game->renderer, x, 0, x, SCREEN_HEIGHT / 2 - wall_height / 2);

        // Draw wall (white)
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(game->renderer, x, SCREEN_HEIGHT / 2 - wall_height / 2, x, SCREEN_HEIGHT / 2 + wall_height / 2);

        // Draw floor (brown)
        SDL_SetRenderDrawColor(game->renderer, 139, 69, 19, 255);
        SDL_RenderDrawLine(game->renderer, x, SCREEN_HEIGHT / 2 + wall_height / 2, x, SCREEN_HEIGHT);
    }

    SDL_RenderPresent(game->renderer);
}

int main(void) {
    Game game;

    if (!init_game(&game)) {
        return 1;
    }

    while (game.running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                game.running = false;
            }
        }

        handle_input(&game);
        raycast(&game);

        SDL_Delay(16);  // ~60 FPS
    }

    cleanup(&game);
    return 0;
}