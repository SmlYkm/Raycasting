#include "graphic/Canvas.hpp"

namespace engine {
    namespace graphic {
        Canvas *Canvas::instance_p(nullptr);


        Canvas::Canvas() :
            height_m(0),
            width_m(0),
            canvas_m(nullptr),
            raycaster_m(nullptr),  // fallback
            camera_width_m(1),
            player_m(nullptr) {
            raycaster_m = Raycaster::get_instance();
        }

        Canvas::~Canvas() {
            raycaster_m = nullptr;  // No need to deallocate, raycaster is global (Singleton)
            if (canvas_m)
                delete canvas_m;
            canvas_m = nullptr;
            if (instance_p)
                delete instance_p;
            instance_p = nullptr;
            player_m = nullptr;
        }

        Canvas *Canvas::get_instance() {
            if (!instance_p)
                instance_p = new Canvas();
            return instance_p;
        }

        void Canvas::set_player(entities::creatures::Player *player) {
            if (!raycaster_m)
                return;
            raycaster_m->set_player(player);
            player_m = player;
        }

        void Canvas::set_level(world::Level *level) {
            if (!raycaster_m)
                return;
            raycaster_m->set_level(level);
        }

        void Canvas::set_canvas_width(const int width) {
            if (width <= 0)
                return;
            if (canvas_m)
                delete[] canvas_m;
            canvas_m = new int[width];
            width_m = width;
        }

        void Canvas::set_canvas_height(const int height) {
            if (height <= 0)
                return;
            height_m = height;
        }

        void Canvas::set_camera_len(const math::FixedPointInt32& len) {
            if (len <= 0)
                return;
            camera_width_m = len;
        }

        int Canvas::operator[](const int idx) const {
            if (idx < 0 || idx >= width_m || !canvas_m)
                return -1;
            return canvas_m[idx];
        }

        void Canvas::update() {
            if (!canvas_m || !raycaster_m || !player_m)
                return;

            player_m->norm_angle();  // Most likely redoundant
            const math::Vector2D& player_pos = player_m->get_position();
            const math::Vector2D& player_dir = player_m->get_direction();
            math::Vector2D camera_vec = player_dir.get_orthogonal() * camera_width_m;
            math::Vector2D camera_pos = player_pos + player_dir + camera_vec;
            math::Vector2D dec        = camera_vec * (2/(width_m-1));

            for (int i = 0; i < width_m; ++i) {
                math::Vector2D        hit_pos   = raycaster_m->dda(camera_pos);
                math::FixedPointInt32 perp_dist = (hit_pos - player_pos) * player_dir;
                
                canvas_m[i] = (height_m / perp_dist).floor().get_int();
                if (canvas_m[i] > height_m)
                    canvas_m[i] = height_m;
                    
                camera_pos -= dec;
            }
        }

    //void Renderer::render3d() {
    //    player->normalizeAngle();
//
    //    Math::Vector2D<float> playerDir = Math::Vector2D<float>(std::cos(player->getAngle()), std::sin(player->getAngle()));
    //    Math::Vector2D<float> cameraPlane = playerDir.getOrthogonal() * cameraPlaneLen;
    //    Math::Vector2D<float> increment = cameraPlane * 2.0f / (nRays - 1);
    //    Math::Vector2D<float> cameraPlanePoint = player->getPosition() + playerDir + cameraPlane;
//
    //    for(int i = 0; i < nRays; ++i, cameraPlanePoint -= increment) {
    //        Math::Vector2D<float> hit = Raycaster::castRay(player->getPosition(), cameraPlanePoint, map);
//
    //        float perpDist = (hit-player->getPosition()) * playerDir;
    //                    
    //        int srcX = (hit.getY() - floor(hit.getY())) * 64;
    //        if(Raycaster::hitWasVertical())
    //            srcX = (hit.getX() - floor(hit.getX())) * 64;
    //        
    //        drawSpriteColumn(i * pixelColumnWidth, perpDist, srcX);   
    //    } 
    //}
    }
}