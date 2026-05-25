#include "Level1.hpp"

namespace game {
    
    // A simple 8x8 enclosed room with some pillars
    const char* level1_map = 
        "########"
        "#      #"
        "#  ##  #"
        "#      #"
        "#   #  #"
        "#      #"
        "#      #"
        "########";

    // Pass the map, rows (8), and cols (8) to the base engine class
    Level1::Level1() : engine::world::Level(level1_map, 8, 8) {
    }

    Level1::~Level1() {
    }

    void Level1::run() {
        // In a full game loop, this would loop through entities_list and call update()
        // For our SDL2 test bench, we will manually update the player in main.cpp
    }
}