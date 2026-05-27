#include "handlers/CollisionHandler.hpp"

namespace engine {
    namespace handlers {
        CollisionHandler *CollisionHandler::instance_s(nullptr);

        CollisionHandler::CollisionHandler() :
            level_m(nullptr) {
        }

        CollisionHandler::~CollisionHandler() {
            if (instance_s) {
                delete instance_s;
                instance_s = nullptr;
            }
        }

        CollisionHandler *CollisionHandler::get_instance() {
            if (!instance_s)
                instance_s = new CollisionHandler();
            return instance_s;
        }

        void CollisionHandler::set_world(world::Level *level) {
            level_m = level;
        }
    
        void CollisionHandler::handle_collision(entities::Entity *moving, entities::Entity *stopped) const {
            if (!moving || !stopped)
                return;

            const math::AABB& hitbox_moving = moving->get_hitbox();
            const math::AABB& hitbox_static = stopped->get_hitbox();        

            // Overlaps
            math::FixedPointInt32 left_overlap  = hitbox_moving.x1 - hitbox_static.x0; // (b1.left + b1.width) - b2.left;
            math::FixedPointInt32 right_overlap = hitbox_static.x1 - hitbox_moving.x0; // (b2.left + b2.width) - b1.left;
            math::FixedPointInt32 upper_overlap = hitbox_moving.y1 - hitbox_static.y0; // (b1.top + b1.height) - b2.top;
            math::FixedPointInt32 lower_overlap = hitbox_static.y1 - hitbox_moving.y0; // (b2.top + b2.height) - b1.top;

            if (left_overlap  < 0)  // Get abs
                left_overlap  = -left_overlap ;  
            if (right_overlap < 0)
                right_overlap = -right_overlap; 
            if (upper_overlap < 0)
                upper_overlap = -upper_overlap; 
            if (lower_overlap < 0)
                lower_overlap = -lower_overlap; 

            bool from_left = left_overlap  < right_overlap; // std::abs(left_overlap) < std::abs(right_overlap);
            bool from_top  = upper_overlap < lower_overlap; // std::abs(upper_overlap) < std::abs(lower_overlap);

            math::FixedPointInt32 min_overlap_x = from_left ? left_overlap  : right_overlap;
            math::FixedPointInt32 min_overlap_y = from_top  ? upper_overlap : lower_overlap;

            if (min_overlap_x < 0)  // Get abs
                min_overlap_x = -min_overlap_x;            
            if (min_overlap_y < 0)
                min_overlap_y = -min_overlap_y;

            math::FixedPointInt32 x = moving->get_x();
            math::FixedPointInt32 y = moving->get_y();

            if (min_overlap_x < min_overlap_y) {
                x += from_left ? -min_overlap_x : min_overlap_x;// e1->setPos(e1->getPos().x + minspbX * (fromLeft ? -1 : 1), e1->getPos().y);
            } else {                                            // if(from_top) {
                y += from_top  ? -min_overlap_y : min_overlap_y;
            }                                                   // e1->setPos(e1->getPos().x, e1->getPos().y + minspbY * -1);
                                                                //else {
            moving->set_position(x, y);                         // e1->setPos(e1->getPos().x, e1->getPos().y + minspbY);
                                                                //}
        }

        bool CollisionHandler::check_collision(const math::AABB& hitbox) const {
            math::FixedPointInt32 x0 = hitbox.x0;
            math::FixedPointInt32 x1 = hitbox.x1;
            math::FixedPointInt32 y0 = hitbox.y0;
            math::FixedPointInt32 y1 = hitbox.y1;

            return (
                level_m->is_wall(x0, y0) ||
                level_m->is_wall(x1, y0) || 
                level_m->is_wall(x0, y1) ||
                level_m->is_wall(x1, y1)
            );
        }

        void CollisionHandler::handle_collision(entities::Entity *entity, const math::AABB& prev_pos) const {  // Collision with walls
            if (!entity || !level_m)
                return;

            const math::AABB& hitbox = entity->get_hitbox();//x0y0x1y1
            math::AABB updated_x(
                hitbox.x0, prev_pos.y0,
                hitbox.x1, prev_pos.y1
            );
            math::AABB updated_y(
                prev_pos.x0, hitbox.y0,
                prev_pos.x1, hitbox.y1
            );
        
            math::Vector2D pos(
                (prev_pos.x0 + prev_pos.x1) / 2,
                (prev_pos.y0 + prev_pos.y1) / 2
            );
            math::FixedPointInt32 x = 0;
            math::FixedPointInt32 y = 0;
            bool has_collision = false;

            if (check_collision(updated_x)) {
                has_collision = true;

                if (updated_x.x0 > prev_pos.x0) {
                    x = pos.x.ceil()  - math::FixedPointInt32::eps();
                } else {
                    x = pos.x.floor() + math::FixedPointInt32::eps();
                }
            }

            if (check_collision(updated_y)) {
                has_collision = true;

                if (updated_y.y0 > prev_pos.y0) {
                    y = pos.y.ceil()  - math::FixedPointInt32::eps();
                } else {
                    y = pos.y.floor() + math::FixedPointInt32::eps();
                }
            }

            if (has_collision)
                entity->set_position(x, y);
        }

        // bool Physics::checkCollision(float x, float y, Game::Map* map, float radius) {
        //     return ((map->isWall((int)(x + radius), (int)(y + radius))) ||
        //             (map->isWall((int)(x - radius), (int)(y + radius))) ||
        //             (map->isWall((int)(x + radius), (int)(y - radius))) ||
        //             (map->isWall((int)(x - radius), (int)(y - radius))));
        // }

        // // Updates the player position and checks for wall collisions
        // void Physics::updatePosition(Math::Vector2D<float>& position, float velocity, float angle, Game::Map* map, float radius) {
        //     float yPos = std::sin(angle) * velocity * (float)deltaTime + position.getY();
        //     float xPos = std::cos(angle) * velocity * (float)deltaTime + position.getX();
        // 
        //     if(!checkCollision(xPos, position.getY(), map, radius)) 
        //         position.setX(xPos);
        //     else if(xPos > position.getX())    
        //         position.setX(ceil(position.getX()) - radius - FLOAT_EPSILON);
        //     else    
        //         position.setX(floor(position.getX()) + radius + FLOAT_EPSILON);
        //     
        //     if(!checkCollision(position.getX(), yPos, map, radius))    
        //         position.setY(yPos);
        //     else if(yPos > position.getY())   
        //         position.setY(ceil(position.getY()) - radius - FLOAT_EPSILON);
        //     else  
        //         position.setY(floor(position.getY()) + radius + FLOAT_EPSILON);
        // }

    }
}