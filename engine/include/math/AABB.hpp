#pragma once

#include "Vector2D.hpp"

namespace engine {
    namespace math {
        class AABB {
        private:
            Vector2D topleft_m;
            Vector2D bottomright_m;
            Vector2D dimensions_m;
        
        public:
            AABB(
                const Vector2D& topleft     = Vector2D(),
                const Vector2D& bottomright = Vector2D()
            );
            AABB(
                const Vector2D& topleft,
                const Vector2D& bottomright,
                const Vector2D& center_coordinates
            );
            AABB(const AABB& other);
            ~AABB();

        public:
            AABB& operator=(const AABB& other);

        private:
            bool points_are_valid(const Vector2D& topleft, const Vector2D& bottomright);

        public:
            void update_pos_using_center(const Vector2D& point);
            void update_pos_using_topleft(const Vector2D& point);
            const Vector2D topleft() const;
            const Vector2D bottomright() const;

            bool overlaps(const AABB& other) const;
            bool contains(const Vector2D& point) const;
        };
    }
}