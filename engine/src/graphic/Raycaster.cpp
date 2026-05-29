#include "graphic/Raycaster.hpp"

namespace engine {
    namespace graphic{
            Raycaster *Raycaster::instance_p(nullptr);

            Raycaster::Raycaster() : 
                vertical_m(false),
                level_m(nullptr),
                player_m(nullptr) {  // fallback
            }

            Raycaster::~Raycaster() {
                level_m  = nullptr;
                player_m = nullptr;
                if (instance_p)
                    delete instance_p;
                instance_p = nullptr;
            }

            Raycaster *Raycaster::get_instance() {
                if (!instance_p)
                    instance_p = new Raycaster();
                return instance_p;
            }

            void Raycaster::set_level(world::Level *level) {
                level_m = level;
            }

            void Raycaster::set_player(entities::creatures::Player *player) {
                player_m = player;
            }

            bool Raycaster::hit_is_vertical() const {
                return vertical_m;
            }

            math::Vector2D Raycaster::dda(const math::Vector2D& camera) {
                if (!level_m || !player_m)
                    return math::Vector2D(-1, -1);

                math::Vector2D position = player_m->get_position();
                math::FixedPointInt32 slope = (camera.y - position.x) / (camera.x - position.y);

                math::FixedPointInt32 vertical_x = 0;  // Vertical
                math::FixedPointInt32 vertical_y = position.y;
                vertical_y.floor();
                ++vertical_y;
                math::FixedPointInt32 vertical_delta_x = 0;
                math::FixedPointInt32 vertical_delta_y = 1;

                if (camera.y < position.y) {  // Facing down
                    vertical_y -= (math::FixedPointInt32::eps() + 1);
                    --vertical_delta_y;
                }

                vertical_x = (vertical_y - position.y)/slope + position.x;
                vertical_delta_x = vertical_delta_y / slope;

                math::FixedPointInt32 horizontal_x = position.x;  // Horizontal
                horizontal_x.floor();
                ++horizontal_x;
                math::FixedPointInt32 horizontal_y = 0;
                math::FixedPointInt32 horizontal_delta_x = 1;
                math::FixedPointInt32 horizontal_delta_y = 0;

                if (camera.x < position.x) {  // Facing right
                    horizontal_x -= (math::FixedPointInt32::eps() + 1);
                    horizontal_delta_x = -1;
                }

                horizontal_y = (horizontal_x - position.x)*slope + position.y;
                horizontal_delta_y = horizontal_delta_x * slope;

                math::Vector2D horizontal_delta(  // DDA
                    horizontal_delta_x, 
                    horizontal_delta_y
                );
                math::Vector2D vertical_delta(
                    vertical_delta_x,
                    vertical_delta_y
                );

                math::Vector2D vertical_pos(vertical_x, vertical_y);
                math::Vector2D horizontal_pos(horizontal_x, horizontal_y);

                math::Vector2D hit_pos(-1, -1);  // fallback

                do {
                    if ((horizontal_pos-position) < (vertical_pos-position)) {
                        hit_pos         = horizontal_pos;
                        horizontal_pos += horizontal_delta;
                        vertical_m      = false;
                    } else {
                        hit_pos       = vertical_pos;
                        vertical_pos += vertical_delta;
                        vertical_m    = true;
                    }
                } while (!level_m->is_wall(hit_pos));

                return hit_pos;
            }

    //    Math::Vector2D<float> Raycaster::castRay(const Math::Vector2D<float>& castingPos,const Math::Vector2D<float>& cameraPoint, Game::Map* map) {
    //        float slope = (cameraPoint.getY() - castingPos.getY()) / ((cameraPoint.getX() - castingPos.getX()));   
    //
    //        //
    //        // Vertical Axis
    //        //
    //
    //        float verticalX, verticalY = floor(castingPos.getY()) + 1.0f;
    //        float verticalDeltaX, verticalDeltaY = 1.0f;
    //
    //        if(cameraPoint.getY() < castingPos.getY()) {    // Facing downward
    //            verticalY -= (FLOAT_EPSILON + 1.0f);
    //            verticalDeltaY = -1.0f;
    //        }
    //
    //        // Line equation used to find the x position in the first iteration
    //        verticalX = (verticalY - castingPos.getY()) / slope + castingPos.getX();
    //        verticalDeltaX = verticalDeltaY / slope;
    //
    //        //
    //        // Horizontal Axis
    //        //
    //
    //        float horizontalX = floor(castingPos.getX()) + 1.0f, horizontalY;
    //        float horizontalDeltaX = 1.0f, horizontalDeltaY;
    //
    //        if(cameraPoint.getX() < castingPos.getX()) {    // Facing right
    //            horizontalX -= (FLOAT_EPSILON + 1.0f);
    //            horizontalDeltaX = -1.0f;
    //        }
    //    
    //        // Line equation used to find the y position in the first iteration
    //        horizontalY = (horizontalX - castingPos.getX())*slope + castingPos.getY();
    //        horizontalDeltaY = horizontalDeltaX * slope;
    //
    //        //
    //        // DDA
    //        //
    //
    //        Math::Vector2D<float> horizontalDelta(horizontalDeltaX, horizontalDeltaY);
    //        Math::Vector2D<float> verticalDelta(verticalDeltaX, verticalDeltaY);
    //
    //        Math::Vector2D<float> verticalPos(verticalX, verticalY);
    //        Math::Vector2D<float> horizontalPos(horizontalX, horizontalY);
    //
    //        Math::Vector2D<float> hitPos;
    //        
    //        do {
    //            if((horizontalPos-castingPos) < (verticalPos-castingPos)) {
    //                hitPos = horizontalPos;
    //                horizontalPos += horizontalDelta;
    //                hitIsVertical = false;
    //            } else {
    //                hitPos = verticalPos;
    //                verticalPos += verticalDelta;
    //                hitIsVertical = true;
    //            }
    //        } while(!map->isWall((int)hitPos.getX(), (int)hitPos.getY()));
    //
    //        return hitPos;
    //    }
    }
}