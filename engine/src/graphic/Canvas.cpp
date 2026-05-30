#include "graphic/Canvas.hpp"
#include "graphic/Raycaster.hpp"
#include "entities/creatures/Player.hpp"
#include "math/Vector2D.hpp"
#include <iostream>

namespace engine {
    namespace graphic {
        Canvas *Canvas::instance_p(nullptr);

        Canvas::Canvas() :
            height_m(0),
            width_m(0),
            canvas_m(nullptr),
            ray_hits_m(nullptr), // <-- Initialize
            raycaster_m(nullptr),  
            camera_width_m(1),
            player_m(nullptr) {
            raycaster_m = Raycaster::get_instance();
        }

        Canvas::~Canvas() {
            raycaster_m = nullptr;  
            if (canvas_m) delete[] canvas_m;
            if (ray_hits_m) delete[] ray_hits_m; // <-- Cleanup
            canvas_m = nullptr;
            ray_hits_m = nullptr;
            if (instance_p) delete instance_p;
            instance_p = nullptr;
            player_m = nullptr;
        }

        Canvas *Canvas::get_instance() {
            if (!instance_p) instance_p = new Canvas();
            return instance_p;
        }

        void Canvas::set_player(entities::creatures::Player *player) {
            if (!raycaster_m) return;
            raycaster_m->set_player(player);
            player_m = player;
        }

        void Canvas::set_level(world::Level *level) {
            if (!raycaster_m) return;
            raycaster_m->set_level(level);
        }

        void Canvas::set_canvas_width(const int width) {
            if (width <= 0) return;
            if (canvas_m) delete[] canvas_m;
            if (ray_hits_m) delete[] ray_hits_m; // <-- Resize array

            canvas_m = new int[width];
            ray_hits_m = new math::Vector2D[width]; // <-- Allocate array
            width_m = width;
        }

        void Canvas::set_canvas_height(const int height) {
            if (height <= 0) return;
            height_m = height;
        }

        void Canvas::set_camera_len(const math::FixedPointInt32& len) {
            if (len <= 0) return;
            camera_width_m = len;
        }

        int Canvas::operator[](const int idx) const {
            if (idx < 0 || idx >= width_m || !canvas_m) return -1;
            return canvas_m[idx];
        }

        math::Vector2D Canvas::get_ray_hit(const int idx) const { // <-- Implementation
            if (idx < 0 || idx >= width_m || !ray_hits_m) return math::Vector2D(-1, -1);
            return ray_hits_m[idx];
        }

        void Canvas::update() {
            if (!canvas_m || !raycaster_m || !player_m) return;

            player_m->norm_angle();  
            const math::Vector2D& player_pos = player_m->get_position();
            const math::Vector2D& player_dir = player_m->get_direction();
            math::Vector2D camera_vec = player_dir.get_orthogonal() * camera_width_m;
            math::Vector2D camera_pos = player_pos + player_dir + camera_vec;
            math::Vector2D dec        = camera_vec * (math::FixedPointInt32(2)/(math::FixedPointInt32(width_m)-math::FixedPointInt32(1)));

            for (int i = 0; i < width_m; ++i) {
                // math::Vector2D hit_pos = raycaster_m->dda(camera_pos);
                math::Vector2D hit_pos_h = raycaster_m->dda_h(camera_pos) - player_pos;
                math::Vector2D hit_pos_v = raycaster_m->dda_v(camera_pos) - player_pos;
                math::Vector2D hit_pos = (hit_pos_h <= hit_pos_v) ? hit_pos_h : hit_pos_v;
                
                ray_hits_m[i] = hit_pos+player_pos; // <-- Cache the hit position

                math::FixedPointInt32 perp_dist = hit_pos * player_dir;
                
                canvas_m[i] = (height_m / perp_dist).floor().get_int();

                if (canvas_m[i] < 5) {
                    std::cout << "direction = " << camera_pos - player_dir << std::endl;
                    std::cout << "hit pos   = " << ray_hits_m[i] << std::endl;
                    std::cout << "hit pos v = " << hit_pos_v << " len = " << hit_pos_v.length_squared() << std::endl;
                    std::cout << "hit pos h = " << hit_pos_h << " len = " << hit_pos_h.length_squared() << std::endl;
                } 

                if (canvas_m[i] > height_m) canvas_m[i] = height_m;

                camera_pos -= dec;
            }
        }
    }
}