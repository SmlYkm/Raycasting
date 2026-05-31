#include <iostream>
#include <ncurses.h>
#include <unistd.h>   // For usleep()
#include <SDL2/SDL.h> // SDL for inputs

#include "Level1.hpp"
#include "entities/creatures/Player.hpp"
#include "handlers/CollisionHandler.hpp"
#include "graphic/Canvas.hpp"
#include "graphic/Raycaster.hpp"
#include "math/Trig.hpp"

#define BUFLEN 9

using namespace engine;
using namespace engine::math;

int main() {
    // _\|/_ Ncurses Initialization _\|/_
    initscr();              
    noecho();               
    cbreak();               
    nodelay(stdscr, TRUE);  
    keypad(stdscr, TRUE);   
    curs_set(0);            

    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLACK);  // Wall
        init_pair(2, COLOR_CYAN, COLOR_BLACK);   // Ceiling
        init_pair(3, COLOR_GREEN, COLOR_BLACK);  // Floor
    }

    int term_w, term_h;
    getmaxyx(stdscr, term_h, term_w); 

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        endwin();
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        return 1;
    }

    // _\|/_ Input handler _\|/_
    SDL_Window* input_window = SDL_CreateWindow(
        "Input Window (Keep Focused!)", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        300, 100, 
        SDL_WINDOW_SHOWN
    );

    if (!input_window) {
        endwin();
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    // _\|/_ Engine Initialization _\|/_
    game::Level1 level;
    handlers::CollisionHandler* collision = handlers::CollisionHandler::get_instance();
    collision->set_world(&level);
    entities::Entity::set_world(&level);

    AABB player_hitbox(
        FixedPointInt32(-25, 2), FixedPointInt32(-25, 2), 
        FixedPointInt32(25, 2),  FixedPointInt32(25, 2)   
    );

    entities::creatures::Player player(
        FixedPointInt32(15, 1), FixedPointInt32(15, 1), 
        player_hitbox,
        FixedPointInt32(4, 2), 
        Vector2D(FixedPointInt32(1), FixedPointInt32(0)), 
        FixedPointInt32(0), 
        FixedPointInt32(2)  
    );

    graphic::Canvas* canvas = graphic::Canvas::get_instance();
    canvas->set_player(&player);
    canvas->set_level(&level);
    canvas->set_canvas_width(term_w);
    canvas->set_canvas_height(term_h);
    canvas->set_camera_len(FixedPointInt32(52, 2)); 

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        int new_w, new_h;  // Handle resizing
        getmaxyx(stdscr, new_h, new_w);

        if (new_w != term_w || new_h != term_h) {
            term_w = new_w;
            term_h = new_h;
            canvas->set_canvas_width(term_w);
            canvas->set_canvas_height(term_h);
        }

        while (SDL_PollEvent(&e) != 0)  // SDL input
            if (e.type == SDL_QUIT)
                quit = true;


        const Uint8* keys = SDL_GetKeyboardState(NULL);

        player.set_state(entities::creatures::Creature::Idle);
        
        // if (keys[SDL_SCANCODE_Q] || keys[SDL_SCANCODE_ESCAPE]) {
        //     quit = true; 
        // }
        
        if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP]) {
            player.set_state(entities::creatures::Creature::Forward); 
            player.update(); 
        }
        if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN]) {
            player.set_state(entities::creatures::Creature::Backward); 
            player.update(); 
        }
        if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]) {
            player.set_state(entities::creatures::Creature::Left); 
            player.update(); 
        }
        if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) {
            player.set_state(entities::creatures::Creature::Right); 
            player.update(); 
        }

        canvas->update();  // _\|/_ Rendering _\|/_
        erase(); 

        for (int x = 0; x < term_w; ++x) {
            int line_height = (*canvas)[x];
            if (line_height < 0) 
                line_height = 0;

            int start_y = (term_h - line_height) / 2;  
            int end_y   = (term_h + line_height) / 2;

            for (int y = 0; y < term_h; ++y) {
                if (y < start_y) {  // Ceiling
                    attron(COLOR_PAIR(2));
                    mvaddch(y, x, ' '); 
                    attroff(COLOR_PAIR(2));
                } else if (y >= start_y && y <= end_y) {
                    attron(COLOR_PAIR(1));   // Wall
                    char c = '.';

                    int v_thresh[BUFLEN] = {
                        999,  
                        999,   
                        999, 
                        26+5,  
                        19+5, 
                        12+5, 
                        12, 
                        7, 
                        3
                    };
                    int h_thresh[BUFLEN] = {
                        33+5 ,  
                        27+5,   
                        22+5, 
                        16+5,  
                        10+5,  
                        4+5, 
                        4, 
                        2, 
                        1
                    };

                    int chars[BUFLEN]    = {
                        '#', 
                        '@', 
                        '$', 
                        '!', 
                        ';', 
                        ':', 
                        '^', 
                        '~', 
                        ','
                    };

                    int *thresh = (*canvas)(x) ? v_thresh : h_thresh;

                    for (int i = 0; i < BUFLEN; ++i) {
                        if (line_height > thresh[i]) {
                            c = chars[i];
                            break;
                        }
                    }

                    mvaddch(y, x, c); 
                    attroff(COLOR_PAIR(1));
                } else {
                    attron(COLOR_PAIR(3));  // Floor
                    mvaddch(y, x, '*');
                    attroff(COLOR_PAIR(3));
                }
            }
        }

        refresh(); 
        usleep(16000); 
    }

    endwin(); 
    SDL_DestroyWindow(input_window);
    SDL_Quit();

    return 0;
}