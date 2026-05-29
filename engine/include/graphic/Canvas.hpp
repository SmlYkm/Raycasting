#pragma once

#include "math/FixedPointInt32.hpp"
#include "graphic/Raycaster.hpp"
#include "entities/creatures/Player.hpp"
#include "world/Level.hpp"

namespace engine {
    namespace graphic {
        class Canvas {
        private:
            int                   height_m;
            int                   width_m;
            int                  *canvas_m;
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
            void update();
        };
    }
}