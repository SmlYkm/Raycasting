#include "math/Trig.hpp"
#include "entities/creatures/Player.hpp"
#include "handlers/CollisionHandler.hpp"

#ifdef RAYCASTING_ENGINE_DEBUG
#include <iostream>
#endif

namespace engine{
    namespace entities {
        namespace creatures {
            Player::Player(
                const math::FixedPointInt32& x,
                const math::FixedPointInt32& y,
                const math::AABB&            hitbox,
                const math::FixedPointInt32& velocity,
                const math::Vector2D&        direction,
                const math::FixedPointInt32& angle,
                const math::FixedPointInt32& angular_velocity
            ) : Creature(
                    math::Vector2D(x, y),
                    hitbox,
                    velocity,
                    direction,
                    angle,
                    angular_velocity
                ) {
            }
            
            Player::~Player() {
            }

            // Right,
            // Left,
            // Forward,
            // Backward,
            // Idle

            void Player::update_pos(State dir) {
                math::FixedPointInt32 y = y_m;
                math::FixedPointInt32 x = x_m;

                if (dir == Forward) {
                    y += direction_m.y * velocity_m;
                    x += direction_m.x * velocity_m;
                } else {
                    y -= direction_m.y * velocity_m;
                    x -= direction_m.x * velocity_m;
                }

                math::AABB next_x = hitbox_m;
                math::AABB next_y = hitbox_m;
                next_x.move_to(x, y_m);
                next_y.move_to(x_m, y);

                if (!collision_handler_p->check_collision(next_x)) {
                    x_m = x;
                } else if (x > x_m) {
                    x_m = x_m.ceil();
                    x_m -= (math::FixedPointInt32::eps() + hitbox_len_m.x/2);
                } else {
                    x_m = x_m.floor(); 
                    x_m += (math::FixedPointInt32::eps() + hitbox_len_m.x/2);
                }
                

                if (!collision_handler_p->check_collision(next_y)) {
                    y_m = y;
                } else if (y > y_m) {
                    y_m = y_m.ceil();
                    y_m -= (math::FixedPointInt32::eps() + hitbox_len_m.y/2);
                } else {
                    y_m = y_m.floor();
                    y_m += (math::FixedPointInt32::eps() + hitbox_len_m.y/2);
                }

                hitbox_m.move_to(x_m, y_m);
            // void updatePosition(Math::Vector2D<float>& position, float velocity, float angle, Game::Map* map, float radius) {
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

            void Player::update() {
                math::AABB prev_pos(hitbox_m);
                switch (state_m) {
                case Forward:
                    update_pos(Forward);
                    break;
                
                case Backward:
                    update_pos(Backward);
                    break;
                
                case Right:
                    angle_m -= angular_velocity_m;
                    norm_angle();
                    update_direction();
                    break;

                case Left:
                    angle_m += angular_velocity_m;
                    norm_angle();
                    update_direction();
                    break;

                default:
                    break;
                }
            }
        }
    }
}