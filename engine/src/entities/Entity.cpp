#include "entities/Entity.hpp"

namespace engine {
    namespace entities {
        world::Level* Entity::world_p(nullptr);

        Entity::Entity(const math::Vector2D& position, const math::AABB& hitbox) 
            : position_m(position)
            , hitbox_m(hitbox) {
        }

        Entity::~Entity() {
        }

        void Entity::set_world(world::Level* new_level) {
            world_p = new_level;
        }

        void Entity::set_position(const math::Vector2D& position) {
            position_m = position;
        }

        const math::Vector2D& Entity::get_position() const {
            return position_m;
        }

        void Entity::set_hitbox(const math::AABB& hitbox) {
            hitbox_m = hitbox;
        }

        const math::AABB& Entity::get_hitbox() const {
            return hitbox_m;
        }
    }
}