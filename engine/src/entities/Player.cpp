#include "math/Trig.hpp"
#include "entities/Player.hpp"

namespace engine{
    namespace entities {
        Player::Player(
            const math::Vector2D&      position,
            const math::AABB&          hitbox,
            const math::FixedPointInt& velocity,
            const math::Vector2D&      direction,
            const math::FixedPointInt& angle,
            const math::FixedPointInt& angular_velocity
        )   : Creature(
                position,
                hitbox,
                velocity,
                direction,
                angle,
                angular_velocity
            ) {
        }
        
        Player::~Player() {
        }

        void Player::update() {

        }

        void Player::update() {
            if (world_p == nullptr || state_m == Idle) {
                return;
            }

            // Update direction vector from the current viewing angle
            // Angle_m is in degrees from 0 to 360
            direction_m.x = math::Trig::cos(angle_m);
            direction_m.y = math::Trig::sin(angle_m);

            // Calculate the intended movement delta based on the current state
            math::Vector2D movement(0, 0);

            switch (state_m) {
                case Forward:
                    movement = direction_m * velocity_m;
                    break;
                case Backward:
                    movement = direction_m * (velocity_m * -1);
                    break;
                case Left:
                    // get_orthogonal() returns (y, -x)
                    movement = direction_m.get_orthogonal() * velocity_m;
                    break;
                case Right:
                    movement = direction_m.get_orthogonal() * (velocity_m * -1);
                    break;
                case Idle:
                    break;
            }

            if (movement.x == 0 && movement.y == 0) {
                return;
            }

            math::Vector2D original_pos = position_m;

            // Move x and check for collisions
            position_m.x += movement.x;
            hitbox_m.update_pos_using_center(position_m);

            if (world_p->hitbox_overlaps_wall(hitbox_m)) {
                // Cancel x and snap hitbox back
                position_m.x = original_pos.x;
                hitbox_m.update_pos_using_center(position_m);
            }

            // Move y and check for collisions
            position_m.y += movement.y;
            hitbox_m.update_pos_using_center(position_m);

            if (world_p->hitbox_overlaps_wall(hitbox_m)) {
                // Cancel y and snap hitbox back
                position_m.y = original_pos.y;
                hitbox_m.update_pos_using_center(position_m);
            }
        }
    }
}