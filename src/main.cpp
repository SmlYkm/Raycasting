// src/main.cpp
#include <iostream>
#include <SDL2/SDL.h>

#include "Level1.hpp"
#include "entities/creatures/Player.hpp"
#include "handlers/CollisionHandler.hpp"
#include "graphic/Canvas.hpp"
#include "graphic/Raycaster.hpp"
#include "math/Trig.hpp"

// Split screen: 2D Top-Down on the left, 3D Raycasting on the right
const int TILE_SIZE = 64; 
const int MAP_WIDTH = 8;
const int MAP_HEIGHT = 8;
const int VIEWPORT_WIDTH = MAP_WIDTH * TILE_SIZE;
const int WINDOW_WIDTH = VIEWPORT_WIDTH * 2;
const int WINDOW_HEIGHT = MAP_HEIGHT * TILE_SIZE;

using namespace engine;
using namespace engine::math;

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Raycasting Engine - Custom Build Testbench", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        WINDOW_WIDTH, WINDOW_HEIGHT, 
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // --- Engine Initialization ---
    game::Level1 level;
    handlers::CollisionHandler* collision = handlers::CollisionHandler::get_instance();
    collision->set_world(&level);
    entities::Entity::set_world(&level);

    // --- Player Initialization ---
    AABB player_hitbox(
        FixedPointInt32(-25, 2), FixedPointInt32(-25, 2), // -0.25, -0.25
        FixedPointInt32(25, 2),  FixedPointInt32(25, 2)   //  0.25,  0.25
    );

    entities::creatures::Player player(
        FixedPointInt32(15, 1), FixedPointInt32(15, 1), // x=1.5, y=1.5
        player_hitbox,
        FixedPointInt32(5, 2), // velocity = 0.05
        Vector2D(FixedPointInt32(1), FixedPointInt32(0)), // Pointing Right
        FixedPointInt32(0), // angle
        FixedPointInt32(2)  // turn speed
    );

    // --- Graphics Initialization ---
    graphic::Canvas* canvas = graphic::Canvas::get_instance();
    canvas->set_player(&player);
    canvas->set_level(&level);
    canvas->set_canvas_width(VIEWPORT_WIDTH); // Canvas handles the 3D half
    canvas->set_canvas_height(WINDOW_HEIGHT);
    canvas->set_camera_len(FixedPointInt32(52, 2)); // 0.66 standard FOV plane

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        // --- 1. Handle Input ---
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) quit = true;
        }

        const Uint8* keys = SDL_GetKeyboardState(NULL);
        
        player.set_state(entities::creatures::Creature::Idle);

        if (keys[SDL_SCANCODE_W]) { 
            player.set_state(entities::creatures::Creature::Forward);
            player.update();
        }
        if (keys[SDL_SCANCODE_S]) { 
            player.set_state(entities::creatures::Creature::Backward);
            player.update();
        }
        if (keys[SDL_SCANCODE_A]) { 
            player.set_state(entities::creatures::Creature::Left);
            player.update();
        }
        if (keys[SDL_SCANCODE_D]) { 
            player.set_state(entities::creatures::Creature::Right);
            player.update();
        }

        // --- 2. Update Systems ---
        canvas->update();

        // --- 3. Render ---
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // ==== LEFT HALF: 2D Top-Down View ====
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); 
        for (int y = 0; y < level.rows(); ++y) {
            for (int x = 0; x < level.cols(); ++x) {
                if (level.get_tile(y, x) == '#') {
                    SDL_Rect wallRect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE - 1, TILE_SIZE - 1 };
                    SDL_RenderFillRect(renderer, &wallRect);
                }
            }
        }

        int px = (player.get_x() * TILE_SIZE).get_int();
        int py = (player.get_y() * TILE_SIZE).get_int();

        // --- NEW: Render Rays ---
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // Enable alpha blending
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 50);         // Transparent yellow

        for (int i = 0; i < VIEWPORT_WIDTH; ++i) {
            Vector2D hit = canvas->get_ray_hit(i);
            if (hit.x != -1) { // -1 is our fallback invalid vector
                int hx = (hit.x * TILE_SIZE).get_int();
                int hy = (hit.y * TILE_SIZE).get_int();
                SDL_RenderDrawLine(renderer, px, py, hx, hy);
            }
        }
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE); // Disable blending
        // ------------------------

        AABB hb = player.get_hitbox();
        int hw = ((hb.x1 - hb.x0) * TILE_SIZE).get_int();
        int hh = ((hb.y1 - hb.y0) * TILE_SIZE).get_int();
        
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect playerRect = { px - (hw/2), py - (hh/2), hw, hh };
        SDL_RenderFillRect(renderer, &playerRect);

        Vector2D dir = player.get_direction();
        int line_end_x = px + (dir.x * TILE_SIZE).get_int();
        int line_end_y = py + (dir.y * TILE_SIZE).get_int();
        
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderDrawLine(renderer, px, py, line_end_x, line_end_y);

        // ==== RIGHT HALF: 3D Raycast View ====
        for (int i = 0; i < VIEWPORT_WIDTH; ++i) {
            int line_height = (*canvas)[i];
            if (line_height < 0) line_height = 0; 

            SDL_SetRenderDrawColor(renderer, 50, 50, 100, 255); // Ceiling
            SDL_RenderDrawLine(renderer, VIEWPORT_WIDTH + i, 0, VIEWPORT_WIDTH + i, (WINDOW_HEIGHT - line_height) / 2);

            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // Wall
            SDL_RenderDrawLine(renderer, VIEWPORT_WIDTH + i, (WINDOW_HEIGHT - line_height) / 2, VIEWPORT_WIDTH + i, (WINDOW_HEIGHT + line_height) / 2);

            SDL_SetRenderDrawColor(renderer, 50, 100, 50, 255); // Floor
            SDL_RenderDrawLine(renderer, VIEWPORT_WIDTH + i, (WINDOW_HEIGHT + line_height) / 2, VIEWPORT_WIDTH + i, WINDOW_HEIGHT);
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, VIEWPORT_WIDTH, 0, VIEWPORT_WIDTH, WINDOW_HEIGHT);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}