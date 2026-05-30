#pragma once

#include "math/Vector2D.hpp"

namespace engine {
    namespace world {
        class Level;  // Forward declaration
    }

    namespace entities {
        namespace creatures {
            class Player;  // Forward declaration
        }
    }

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
            math::Vector2D dda_h(const math::Vector2D& camera);
            math::Vector2D dda_v(const math::Vector2D& camera);
        
        private:
            math::Vector2D dda_perp_v(const math::Vector2D& camera);
            math::Vector2D dda_perp_h(const math::Vector2D& camera);
        };
    }
}