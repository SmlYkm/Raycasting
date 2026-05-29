#pragma once

#include "math/FixedPointInt32.hpp"
#include "math/Vector2D.hpp"
#include "world/Level.hpp"
#include "entities/creatures/Player.hpp"

namespace engine {
    namespace graphic {
        class Raycaster {
        private:
            bool                        vertical_m;
            world::Level                *level_m;
            entities::creatures::Player *player_m;
        
        private:
            static Raycaster *instance_p;

        private:
            Raycaster();
            ~Raycaster();

            Raycaster(Raycaster const&)      = delete;
            Raycaster(Raycaster const&&)     = delete;
            void operator=(Raycaster const&) = delete;
            void operator=(Raycaster const&&)= delete;

        public:
            static Raycaster *get_instance();


        public:
            void set_level(world::Level *level);
            void set_player(entities::creatures::Player *player);

            bool hit_is_vertical() const;
            math::Vector2D dda(const math::Vector2D& camera);
        };
    }
}