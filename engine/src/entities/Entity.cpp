#include "entities/Entity.hpp"
#include "handlers/CollisionHandler.hpp"

namespace engine {
    namespace entities {
        world::Level* Entity::world_p(nullptr);

        handlers::CollisionHandler *Entity::collision_handler_p(
            handlers::CollisionHandler::get_instance()
        );

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

        void Entity::set_position(const math::FixedPointInt32& x, const math::FixedPointInt32& y) {
            math::FixedPointInt32 delta_x = x - x_m;
            math::FixedPointInt32 delta_y = y - y_m;
            hitbox_m.move(delta_x, delta_y);
            x_m = x;
            y_m = y;
        }

        void Entity::set_position(const math::Vector2D position) {
            set_position(position.x, position.y);
        }

        void Entity::move(const math::FixedPointInt32& delta_x, const math::FixedPointInt32& delta_y) {
            hitbox_m.move(delta_x, delta_y);
            x_m += delta_x;
            y_m += delta_y;
        }
        
        void Entity::move(const math::Vector2D delta) {
            move(delta.x, delta.y);
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