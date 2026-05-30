#pragma once

#include "math/FixedPointInt32.hpp"
#include "math/Vector2D.hpp"

namespace engine {
    namespace world {
        class Level;  
    }

    namespace entities {
        namespace creatures {
            class Player;  
        }
    }

    namespace graphic {
        class Raycaster;  
    
        class Canvas {
        private:
            int                   height_m;
            int                   width_m;
            int                  *canvas_m;
#ifdef RAYCASTING_ENGINE_DEBUG
            math::Vector2D       *ray_hits_m;
#endif 
            Raycaster            *raycaster_m;
            math::FixedPointInt32 camera_width_m;
            entities::creatures::Player *player_m;

        private:
            static Canvas *instance_p;

        private:
            Canvas();
            ~Canvas();

            Canvas(Canvas const&)         = delete;
            Canvas(Canvas const&&)        = delete;
            void operator=(Canvas const&) = delete;
            void operator=(Canvas const&&)= delete;
        
        public:
            static Canvas *get_instance();

        public:
            void set_player(entities::creatures::Player *player);
            void set_level(world::Level *level);
            void set_canvas_width(const int width);
            void set_canvas_height(const int height);
            void set_camera_len(const math::FixedPointInt32& len);

        public:
            int operator[](const int idx) const;
#ifdef RAYCASTING_ENGINE_DEBUG
            math::Vector2D get_ray_hit(const int idx) const;
#endif
            void update();
        };
    }
}