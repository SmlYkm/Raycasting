#pragma once

#include "Creature.hpp"

namespace engine {
    namespace entities {
        class Player : public Creature {
        public:
            Player(
                const math::Vector2D&      position         = math::Vector2D(),
                const math::AABB&          hitbox           = math::AABB(),
                const math::FixedPointInt32& velocity         = math::FixedPointInt32(),
                const math::Vector2D&      direction        = math::Vector2D(),
                const math::FixedPointInt32& angle            = math::FixedPointInt32(),
                const math::FixedPointInt32& angular_velocity = math::FixedPointInt32()
            );
            ~Player();
        
        public:
            void update();
        };
    }
}