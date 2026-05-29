// src/main.cpp
#include <iostream>
#include <SDL2/SDL.h>

#include "Level1.hpp"
#include "entities/creatures/Player.hpp"
#include "handlers/CollisionHandler.hpp"
#include "math/Trig.hpp"

// Constants for our top-down rendering
const int TILE_SIZE = 64; 
const int MAP_WIDTH = 8;
const int MAP_HEIGHT = 8;
const int WINDOW_WIDTH = MAP_WIDTH * TILE_SIZE;
const int WINDOW_HEIGHT = MAP_HEIGHT * TILE_SIZE;

using namespace engine;
using namespace engine::math;

int main() {
    for (int i = 0; i < 360; ++i) {
        std::cout << math::Trig::sin(i) << std::endl;
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Raycasting Engine - Collision Test", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        WINDOW_WIDTH, WINDOW_HEIGHT, 
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Initialize Level and Handler
    game::Level1 level;
    handlers::CollisionHandler* collision = handlers::CollisionHandler::get_instance();
    collision->set_world(&level);
    entities::Entity::set_world(&level);

    // Initialize Player
    // Starting at grid position (1.5, 1.5) to be inside the walls
    // Setting velocity to ~0.05 per frame
    // Hitbox is slightly smaller than a full tile (e.g., 0.25 offset from center)
    AABB player_hitbox(
        FixedPointInt32(-25, 2), FixedPointInt32(-25, 2), // -0.25, -0.25
        FixedPointInt32(25, 2),  FixedPointInt32(25, 2)   //  0.25,  0.25
    );

    entities::Player player(
        FixedPointInt32(15, 1), FixedPointInt32(15, 1), // x=1.5, y=1.5
        player_hitbox,
        FixedPointInt32(5, 2), // velocity = 0.05
        Vector2D(FixedPointInt32(1), FixedPointInt32(0)), // pointing Right
        0, // angle
        FixedPointInt32(1) // turn speed
    );

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        // 1. Handle Input
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        
        player.set_state(entities::Creature::Idle);

        if (currentKeyStates[SDL_SCANCODE_W]) {
            player.set_state(entities::Creature::Forward);
            player.update();
        } else if (currentKeyStates[SDL_SCANCODE_S]) {
            player.set_state(entities::Creature::Backward);
            player.update();
        }
        
        // We still need to call update() if turning so angle changes
        // But your current update() uses a switch statement for state_m
        // For testing, we'll brute force rotation and then call update for movement
        if (currentKeyStates[SDL_SCANCODE_A]) {

            player.set_state(entities::Creature::Left);
            player.update();
        } else if (currentKeyStates[SDL_SCANCODE_D]) {
            player.set_state(entities::Creature::Right);
            player.update();
        }

        // 3. Render
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render Map
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White walls
        for (int y = 0; y < level.rows(); ++y) {
            for (int x = 0; x < level.cols(); ++x) {
                if (level.get_tile(y, x) == '#') {
                    SDL_Rect wallRect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
                    SDL_RenderFillRect(renderer, &wallRect);
                }
            }
        }

        // Render Player
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red player
        
        // Convert FixedPointInt32 Q16.16 to integer pixel coordinates
        int px = (player.get_x().get_int() * TILE_SIZE) + (player.get_x().get_frac() * TILE_SIZE / 65536);
        int py = (player.get_y().get_int() * TILE_SIZE) + (player.get_y().get_frac() * TILE_SIZE / 65536);
        
        // Render based on hitbox size (relative to player pos)
        AABB hb = player.get_hitbox();
        int hw = ((hb.x1 - hb.x0).get_int() * TILE_SIZE) + ((hb.x1 - hb.x0).get_frac() * TILE_SIZE / 65536);
        int hh = ((hb.y1 - hb.y0).get_int() * TILE_SIZE) + ((hb.y1 - hb.y0).get_frac() * TILE_SIZE / 65536);
        
        SDL_Rect playerRect = { 
            px - (hw/2), 
            py - (hh/2), 
            hw, 
            hh 
        };
        SDL_RenderFillRect(renderer, &playerRect);

        // Render Direction line
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green line
        // We have to calculate direction from angle manually here because direction_m is protected
        // For testing, we just draw a small line from center
        // To do this properly, we'd need a getter for direction_m in Creature.hpp
        
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // ~60fps
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}