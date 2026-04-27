#pragma once

#include "Creature.hpp"

namespace engine {
    namespace entities {
        class Player : public Creature {
        public:
            Player(
                const math::Vector2D&      position         = math::Vector2D(),
                const math::AABB&          hitbox           = math::AABB(),
                const math::FixedPointInt& velocity         = math::FixedPointInt(),
                const math::Vector2D&      direction        = math::Vector2D(),
                const math::FixedPointInt& angle            = math::FixedPointInt(),
                const math::FixedPointInt& angular_velocity = math::FixedPointInt()
            );
            ~Player();
        
        public:
            void update();
        };
    }
}