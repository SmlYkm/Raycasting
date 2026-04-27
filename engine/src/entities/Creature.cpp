#include "entities/Creature.hpp"

namespace engine {
    namespace entities {
        Creature::Creature(
            const math::Vector2D&      position,
            const math::AABB&          hitbox,
            const math::FixedPointInt& velocity,
            const math::Vector2D&      direction,
            const math::FixedPointInt& angle,
            const math::FixedPointInt& angular_velocity
        )   : Entity(position, hitbox)
            , state_m(Idle)
            , velocity_m(velocity)
            , direction_m(direction)
            , angle_m(angle)
            , angular_velocity_m(angular_velocity) {
        }
        
        Creature::~Creature() {
        }

        void Creature::set_state(State new_state) {
            state_m = new_state;
        }

        Creature::State Creature::get_state() const {
            return state_m;
        }
    }
}