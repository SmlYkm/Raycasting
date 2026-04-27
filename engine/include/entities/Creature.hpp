#pragma once

#include "Entity.hpp"

namespace engine {
    namespace entities {
        class Creature : public Entity {
        protected:
            enum State {
                Right,
                Left,
                Forward,
                Backward,
                Idle
            };

        protected:
            State               state_m;
            math::FixedPointInt velocity_m;
            math::Vector2D      direction_m;
            math::FixedPointInt angle_m;
            math::FixedPointInt angular_velocity_m;

        public:
            Creature(
                const math::Vector2D&      position         = math::Vector2D(),
                const math::AABB&          hitbox           = math::AABB(),
                const math::FixedPointInt& velocity         = math::FixedPointInt(),
                const math::Vector2D&      direction        = math::Vector2D(),
                const math::FixedPointInt& angle            = math::FixedPointInt(),
                const math::FixedPointInt& angular_velocity = math::FixedPointInt()
            );
            virtual ~Creature();

        public:
            void set_state(State new_state);
            State get_state() const;

            virtual void update() = 0;
        };
    }
}