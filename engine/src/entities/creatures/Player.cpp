#include "math/Trig.hpp"
#include "entities/creatures/Player.hpp"

namespace engine{
    namespace entities {
        Player::Player(
            const math::Vector2D&      position,
            const math::AABB&          hitbox,
            const math::FixedPointInt32& velocity,
            const math::Vector2D&      direction,
            const math::FixedPointInt32& angle,
            const math::FixedPointInt32& angular_velocity
        ) : Creature(
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
    }
}