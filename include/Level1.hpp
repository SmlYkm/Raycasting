#pragma once

#include "world/Level.hpp"

namespace game {
    class Level1 : public engine::world::Level {
    public:
        Level1();
        ~Level1();

        void run() override; 
    };
}