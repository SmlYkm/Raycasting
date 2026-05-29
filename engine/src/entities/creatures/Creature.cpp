#include "entities/creatures/Creature.hpp"
#include "math/Trig.hpp"

namespace engine {
    namespace entities {
        Creature::Creature(
            const math::Vector2D&        position,
            const math::AABB&            hitbox,
            const math::FixedPointInt32& velocity,
            const math::Vector2D&        direction,
            const math::FixedPointInt32& angle,
            const math::FixedPointInt32& angular_velocity
        ) : Entity(position, hitbox), 
            state_m(Idle), 
            velocity_m(velocity), 
            direction_m(direction), 
            angle_m(angle), 
            angular_velocity_m(angular_velocity) {
        }
        
        Creature::~Creature() {
        }

        void Creature::norm_angle() {
            while(angle_m >= 360) //[0, 359]
                angle_m -= 360;
            while (angle_m < 0) 
                angle_m += 360;
        }
        
        void Creature::update_direction() {
            math::FixedPointInt32 x = math::Trig::cos(angle_m);
            math::FixedPointInt32 y = math::Trig::sin(angle_m);

            direction_m = math::Vector2D(x, -y);  // Window coords are inverted
        }

        void Creature::set_state(State new_state) {
            state_m = new_state;
        }

        Creature::State Creature::get_state() const {
            return state_m;
        }
    }
}