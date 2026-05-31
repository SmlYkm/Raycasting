#pragma once

#include "math/AABB.hpp"

namespace engine {
    namespace handlers {
        class CollisionHandler; // forward declaration
    }

    namespace world {
        class Level;  // Forward declaration
    }
    
    namespace entities {
        class Entity {
        protected:
            static world::Level* world_p;
            static handlers::CollisionHandler *collision_handler_p;

        protected:
            math::FixedPointInt32 x_m;
            math::FixedPointInt32 y_m;
            math::AABB            hitbox_m;
            math::Vector2D        hitbox_len_m;
        
        public:
            Entity(
                const math::Vector2D& position = math::Vector2D(),
                const math::AABB&     hitbox   = math::AABB()
            );
            virtual ~Entity();

        public:
            static void set_world(world::Level* new_level);
        
        public:
            virtual void set_position(math::FixedPointInt32 x, math::FixedPointInt32 y);
            virtual void set_position(const math::Vector2D position);
            virtual math::Vector2D get_position() const;
            virtual void move(math::FixedPointInt32 delta_x, math::FixedPointInt32 delta_y);
            virtual void move(const math::Vector2D delta);

            virtual void set_hitbox(const math::AABB& hitbox);
            virtual const math::AABB& get_hitbox() const;

            virtual void update() = 0;

            math::FixedPointInt32 get_x() const;
            math::FixedPointInt32 get_y() const;
        };
    }
}