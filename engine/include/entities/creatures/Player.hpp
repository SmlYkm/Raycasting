#pragma once

#include "Creature.hpp"

namespace engine {
    namespace entities {
        class Player : public Creature {
        public:
            Player(
                const math::FixedPointInt32& x                = math::FixedPointInt32(),
                const math::FixedPointInt32& y                = math::FixedPointInt32(),
                const math::AABB&            hitbox           = math::AABB(),
                const math::FixedPointInt32& velocity         = math::FixedPointInt32(),
                const math::Vector2D&        direction        = math::Vector2D(),
                int                          angle            = 0,
                const math::FixedPointInt32& angular_velocity = math::FixedPointInt32()
            );
            ~Player();

        public:
            void update();
        };
    }
}