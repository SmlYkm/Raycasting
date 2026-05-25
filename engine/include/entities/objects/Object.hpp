#pragma once

#include "Entity.hpp"

namespace engine {
    namespace entities {
        namespace objects {
            class Object : public Entity {
            private:
                bool can_collide_m;

            public:
                Object(
                    const math::FixedPointInt32 x = math::FixedPointInt32(),
                    const math::FixedPointInt32 y = math::FixedPointInt32(),
                    const math::AABB&      hitbox = math::AABB(),
                    const bool        can_collide = true
                );
                ~Object();

            public:
                bool can_collide() const;
            };
        }
    }
}