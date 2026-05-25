#pragma once

#include "world/Level.hpp"

namespace game {
    class Level1 : public engine::world::Level {
    public:
        Level1();
        ~Level1();

        // Must override the pure virtual function!
        void run() override; 
    };
}