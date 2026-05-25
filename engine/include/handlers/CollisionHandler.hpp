#pragma once

#include "world/Level.hpp"
#include "entities/Entity.hpp"

namespace engine {
    namespace handlers {
        class CollisionHandler {  // Singleton
        private:
            static CollisionHandler *instance_s;
            world::Level *level_m;

        private:
            CollisionHandler();
            
            CollisionHandler(const CollisionHandler& other) = delete;
            CollisionHandler(CollisionHandler& other) = delete;
            CollisionHandler& operator=(const CollisionHandler& other) = delete;
            CollisionHandler& operator=(CollisionHandler&& other) = delete;

        public:
            CollisionHandler *get_instance() const;

        public:
            void set_world(world::Level *level);

            void handle_collision(entities::Entity *moving, entities::Entity *stopped) const;
        };
    }
}