#pragma once

#include "Creature.hpp"

namespace engine {
    namespace entities {
        namespace creatures {
            class Player : public Creature {
            public:
                Player(
                    math::FixedPointInt32 x                = math::FixedPointInt32(),
                    math::FixedPointInt32 y                = math::FixedPointInt32(),
                    const math::AABB&     hitbox           = math::AABB(),
                    math::FixedPointInt32 velocity         = math::FixedPointInt32(),
                    const math::Vector2D& direction        = math::Vector2D(),
                    math::FixedPointInt32 angle            = math::FixedPointInt32(),
                    math::FixedPointInt32 angular_velocity = math::FixedPointInt32()
                );
                ~Player();

            private:
                void update_pos(State dir);

            public:
                void update();
            };
        }
    }
}