#pragma once

#include "math/AABB.hpp"

namespace engine {
    namespace world {
        class Level;  // Forward declaration
    }

    namespace entities {
        class Entity;  // Forward declaration
    }

    namespace handlers {
        class CollisionHandler {  // Singleton
        private:
            static CollisionHandler *instance_s;
            world::Level *level_m;

        private:
            CollisionHandler();
            ~CollisionHandler();
            
            CollisionHandler(const CollisionHandler& other) = delete;
            CollisionHandler(CollisionHandler& other)       = delete;
            CollisionHandler& operator=(const CollisionHandler& other) = delete;
            CollisionHandler& operator=(CollisionHandler&& other)      = delete;

        public:
            static CollisionHandler *get_instance();

        public:
            void set_world(world::Level *level);

            void handle_collision(entities::Entity *moving, entities::Entity *stopped) const;
            
        public:
            bool check_collision(const math::AABB& hitbox) const;

        public:
            void handle_collision(entities::Entity *entity, const math::AABB& prev_pos) const;
        };
    }
}