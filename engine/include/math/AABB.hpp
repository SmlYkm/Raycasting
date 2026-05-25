#pragma once

#include <iostream>

#include "Vector2D.hpp"
#include "FixedPointInt32.hpp"

namespace engine {
    namespace math {

        class AABB {
        public:                                                                                
            FixedPointInt32 x0, y0;
            FixedPointInt32 x1, y1;

        public:
            AABB(
                FixedPointInt32 x0, FixedPointInt32 y0, 
                FixedPointInt32 x1, FixedPointInt32 y1
            );

            AABB();

        public:
            const AABB& set(
                FixedPointInt32 x0_p, FixedPointInt32 y0_P, 
                FixedPointInt32 x1_p, FixedPointInt32 y1_P
            );

            AABB expand(FixedPointInt32 xa, FixedPointInt32 ya) const;            
            AABB grow(FixedPointInt32 xa, FixedPointInt32 ya) const;

            AABB clone_move(FixedPointInt32 xa, FixedPointInt32 ya) const;
            
            FixedPointInt32 clip_x_collide(const AABB& c, FixedPointInt32 xa) const;
            FixedPointInt32 clip_y_collide(const AABB& c, FixedPointInt32 ya) const;
            
            bool intersects(const AABB& c) const;
            bool intersects_inner(const AABB& c) const;
            
            const AABB& move(FixedPointInt32 xa, FixedPointInt32 ya);
            
            bool intersects(
                FixedPointInt32 x02, FixedPointInt32 y02,
                FixedPointInt32 x12, FixedPointInt32 y12
            ) const;
            
            bool contains(const Vector2D& p) const;

            FixedPointInt32 get_size() const;
            
            AABB shrink(FixedPointInt32 xa, FixedPointInt32 ya);
            AABB copy();
            
            bool intersects_face_x(const Vector2D& v) const;
            bool intersects_face_y(const Vector2D& v) const;

            void set(const AABB& b);
        };
    }
}