#include "entities/objects/Object.hpp"

namespace engine {
    namespace entities {
        namespace objects {
            Object::Object(
                const math::FixedPointInt32 x,
                const math::FixedPointInt32 y,
                const math::AABB&      hitbox,
                const bool        can_collide
            ) : Entity(math::Vector2D(x, y), hitbox),
                can_collide_m(can_collide) {
            }

            Object::~Object() {
            }

            bool Object::can_collide() const {
                return can_collide_m;
            }
        }
    }
}