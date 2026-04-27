#include "math/AABB.hpp"

namespace engine {
    namespace math {
        
        AABB::AABB(const Vector2D& topleft, const Vector2D& bottomright) 
            : topleft_m(Vector2D())      // Fallback Values
            , bottomright_m(Vector2D()) 
            , dimensions_m(Vector2D()) {
            if (points_are_valid(topleft, bottomright)) {
                topleft_m     = topleft;
                bottomright_m = bottomright;
                dimensions_m  = bottomright - topleft;
            }
        }

        AABB::AABB(const Vector2D& topleft, const Vector2D& bottomright, const Vector2D& center_coordinates)
            : topleft_m(Vector2D())
            , bottomright_m(Vector2D())
            , dimensions_m(Vector2D()){
            if (points_are_valid(topleft, bottomright)) {
                topleft_m     = topleft;
                bottomright_m = bottomright;
                dimensions_m  = bottomright - topleft;
                update_pos_using_center(center_coordinates);
            }
        }

        AABB::AABB(const AABB& other)
            : topleft_m(other.topleft_m)
            , bottomright_m(other.bottomright_m)
            , dimensions_m(other.dimensions_m) {
        }

        AABB::~AABB() {
        }

        AABB& AABB::operator=(const AABB& other) {
            topleft_m     = other.topleft_m;
            bottomright_m = other.bottomright_m;
            dimensions_m  = other.dimensions_m;
            return *this;
        }

        bool AABB::points_are_valid(const Vector2D& topleft, const Vector2D& bottomright) {
            return (topleft.x < bottomright.x && topleft.y < bottomright.y);
        }

        void AABB::update_pos_using_center(const Vector2D& point) {
            topleft_m     = point - dimensions_m / 2;
            bottomright_m = point + dimensions_m / 2;
        }

        void AABB::update_pos_using_topleft(const Vector2D& point) {
            topleft_m     = point;
            bottomright_m = point + dimensions_m;
        }

        const Vector2D AABB::topleft() const {
            return topleft_m;
        }

        const Vector2D AABB::bottomright() const {
            return bottomright_m;
        }

        bool AABB::overlaps(const AABB& other) const {
            return (
                (topleft_m.x <= other.bottomright_m.x && bottomright_m.x >= other.topleft_m.x) &&
                (topleft_m.y <= other.bottomright_m.y && bottomright_m.y >= other.topleft_m.y)
            );
        }

        bool AABB::contains(const Vector2D& point) const {
            return (
                (topleft_m.x     <= point.x) && (topleft_m.y     <= point.y) &&
                (bottomright_m.x >= point.x) && (bottomright_m.y >= point.y)
            );
        }        
    }
}