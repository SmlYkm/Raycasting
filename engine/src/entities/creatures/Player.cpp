#include "math/Trig.hpp"
#include "entities/creatures/Player.hpp"
#include "handlers/CollisionHandler.hpp"

namespace engine{
    namespace entities {
        Player::Player(
            const math::FixedPointInt32& x,
            const math::FixedPointInt32& y,
            const math::AABB&            hitbox,
            const math::FixedPointInt32& velocity,
            const math::Vector2D&        direction,
            int                          angle,
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

        void Player::update() {
            math::AABB prev_pos(hitbox_m);
            switch (state_m) {
            case Forward:
                move(direction_m*velocity_m);
                collision_handler_p->handle_collision(this, prev_pos);
                break;
            
            case Backward:
                move(-direction_m*velocity_m);
                collision_handler_p->handle_collision(this, prev_pos);
                break;
            
            case Right:
                angle_m -= velocity_m;
                norm_angle();
                update_direction();
                break;

            case Left:
                angle_m += velocity_m;
                norm_angle();
                update_direction();
                break;

            default:
                break;
            }
        }
    }
}