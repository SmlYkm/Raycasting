#pragma once

#include "math/AABB.hpp"
#include "math/FixedPointInt32.hpp"
#include "world/Level.hpp"

namespace engine {
    namespace entities {
        class Entity {
        protected:
            static world::Level* world_p;

        protected:
            math::FixedPointInt32 x_m;
            math::FixedPointInt32 y_m;
            math::AABB            hitbox_m;
        
        public:
            Entity(
                const math::Vector2D& position = math::Vector2D(),
                const math::AABB&     hitbox   = math::AABB()
            );
            virtual ~Entity();

        public:
            static void set_world(world::Level* new_level);
        
        public:
            virtual void set_position(const math::Vector2D& position);
            virtual math::Vector2D get_position() const;

            virtual void set_hitbox(const math::AABB& hitbox);
            virtual const math::AABB& get_hitbox() const;

            virtual void update() = 0;

            math::FixedPointInt32 get_x() const;
            math::FixedPointInt32 get_y() const;
        };
    }
}