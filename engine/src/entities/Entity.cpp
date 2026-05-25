#include "entities/Entity.hpp"

namespace engine {
    namespace entities {
        world::Level* Entity::world_p(nullptr);

        Entity::Entity(const math::Vector2D& position, const math::AABB& hitbox) : 
            x_m(position.x), 
            y_m(position.y),
            hitbox_m(hitbox) {
        }

        Entity::~Entity() {
        }

        void Entity::set_world(world::Level* new_level) {
            world_p = new_level;
        }

        void Entity::set_position(const math::Vector2D& position) {
            x_m = position.x;
            y_m = position.y;
        }

        math::Vector2D Entity::get_position() const {
            return math::Vector2D(x_m, y_m);
        }

        void Entity::set_hitbox(const math::AABB& hitbox) {
            hitbox_m = hitbox;
        }

        const math::AABB& Entity::get_hitbox() const {
            return hitbox_m;
        }

        math::FixedPointInt32 Entity::get_x() const {
            return x_m;
        }

        math::FixedPointInt32 Entity::get_y() const {
            return y_m;
        }

    }
}