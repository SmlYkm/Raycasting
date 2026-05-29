#pragma once

#include "entities/Entity.hpp"

namespace engine {
    namespace entities {
        namespace creatures {
            class Creature : public Entity {
            public:
                enum State {
                    Right,
                    Left,
                    Forward,
                    Backward,
                    Idle
                };

            protected:
                State                 state_m;
                math::FixedPointInt32 velocity_m;
                math::Vector2D        direction_m;
                math::FixedPointInt32 angle_m;
                math::FixedPointInt32 angular_velocity_m;

            public:
                Creature(
                    const math::Vector2D&        position         = math::Vector2D(),
                    const math::AABB&            hitbox           = math::AABB(),
                    const math::FixedPointInt32& velocity         = math::FixedPointInt32(),
                    const math::Vector2D&        direction        = math::Vector2D(),
                    const math::FixedPointInt32& angle            = math::FixedPointInt32(),
                    const math::FixedPointInt32& angular_velocity = math::FixedPointInt32()
                );
                virtual ~Creature();

            public:
                void set_state(State new_state);
                State get_state() const;
                const math::Vector2D& get_direction() const;

                void norm_angle();
                void update_direction();

                virtual void update() = 0;
            };
        }
    }
}