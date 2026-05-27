#include "math/AABB.hpp"

namespace engine {
    namespace math {
        AABB::AABB(
            FixedPointInt32  x0_p, FixedPointInt32  y0_p, 
            FixedPointInt32  x1_p, FixedPointInt32  y1_p
        ) : x0(x0_p), y0(y0_p),
            x1(x1_p), y1(y1_p) {
        }

        AABB::AABB() : 
            x0(), y0(),
            x1(), y1() {
        }


        const AABB& AABB::set(
            FixedPointInt32  x0, FixedPointInt32  y0, 
            FixedPointInt32  x1, FixedPointInt32  y1
        ) {
            this->x0 = x0;
            this->y0 = y0;
            this->x1 = x1;
            this->y1 = y1;

            return *this;
        }

        AABB AABB::expand(FixedPointInt32  xa, FixedPointInt32  ya) const {
            FixedPointInt32  _x0 = x0;
            FixedPointInt32  _y0 = y0;
            FixedPointInt32  _x1 = x1;
            FixedPointInt32  _y1 = y1;

            if (xa < 0) 
                _x0 += xa;
            if (xa > 0) 
                _x1 += xa;

            if (ya < 0) 
                _y0 += ya;
            if (ya > 0) 
                _y1 += ya;

            return AABB(_x0, _y0, _x1, _y1);
        }

        AABB AABB::grow(FixedPointInt32  xa, FixedPointInt32  ya) const {
            FixedPointInt32  _x0 = x0 - xa;
            FixedPointInt32  _y0 = y0 - ya;

            FixedPointInt32  _x1 = x1 + xa;
            FixedPointInt32  _y1 = y1 + ya;

            return AABB(_x0, _y0, _x1, _y1);
        }

        AABB AABB::clone_move(FixedPointInt32  xa, FixedPointInt32  ya) const {
            return AABB(
                x0+xa, y0+ya, 
                x1+xa, y1+ya
            );
        }

        FixedPointInt32  AABB::clip_x_collide(const AABB& c, FixedPointInt32  xa) const {
            if (c.y1 <= y0 || c.y0 >= y1) 
                return xa;

            if (xa > 0 && c.x1 <= x0) {
                FixedPointInt32  max = x0 - c.x1;
                if (max < xa) 
                    xa = max;
            }
            
            if (xa < 0 && c.x0 >= x1) {
                FixedPointInt32 max = x1 - c.x0;
                if (max > xa) 
                    xa = max;
            }

            return xa;
        }

        FixedPointInt32 AABB::clip_y_collide(const AABB& c, FixedPointInt32  ya) const {
            if (c.x1 <= x0 || c.x0 >= x1) 
                return ya;

            if (ya > 0 && c.y1 <= y0) {
                FixedPointInt32  max = y0 - c.y1;
                if (max < ya) 
                    ya = max;
            }
            if (ya < 0 && c.y0 >= y1) {
                FixedPointInt32  max = y1 - c.y0;
                if (max > ya) 
                    ya = max;
            }

            return ya;
        }

        bool AABB::intersects(const AABB& c) const{
            if (c.x1 <= x0 || c.x0 >= x1) 
                return false;
            if (c.y1 <= y0 || c.y0 >= y1) 
                return false;
            return true;
        }

        bool AABB::intersects_inner(const AABB& c) const {
            if (c.x1 < x0 || c.x0 > x1) 
                return false;
            if (c.y1 < y0 || c.y0 > y1) 
                return false;
            return true;
        }

        const AABB& AABB::move(FixedPointInt32  xa, FixedPointInt32  ya) {
            x0 += xa;
            y0 += ya;

            x1 += xa;
            y1 += ya;

            return *this;
        }

        bool AABB::intersects(
            FixedPointInt32  x02, FixedPointInt32  y02, 
            FixedPointInt32  x12, FixedPointInt32  y12
        ) const {
            if (x12 <= x0 || x02 >= x1) 
                return false;
            if (y12 <= y0 || y02 >= y1) 
                return false;
            return true;
        }

        bool AABB::contains(const Vector2D& p) const {
            if (p.x <= x0 || p.x >= x1) 
                return false;
            if (p.y <= y0 || p.y >= y1) 
                return false;
            return true;
        }

        // 4J Added
        // bool AABB::containsIncludingLowerBound(const Vector2D& p) const {
        //     if (p.x < x0 || p.x >= x1) 
        //         return false;
        //     if (p.y < y0 || p.y >= y1) 
        //         return false;
        //     return true;
        // }

        FixedPointInt32 AABB::get_size() const {
            FixedPointInt32  xs = x1 - x0;
            FixedPointInt32  ys = y1 - y0;
            return (xs + ys) / FixedPointInt32(2, true);
        }

        AABB AABB::shrink(FixedPointInt32  xa, FixedPointInt32  ya) {
            FixedPointInt32  _x0 = x0 + xa;
            FixedPointInt32  _y0 = y0 + ya;

            FixedPointInt32  _x1 = x1 - xa;
            FixedPointInt32  _y1 = y1 - ya;


            return AABB(_x0, _y0, _x1, _y1);
        }

        AABB AABB::copy() {
            return AABB(x0, y0, x1, y1);
        }

//    HitResult *AABB::clip(const Vector2D& a, const Vector2D& b) const {
//        Vector2D *xh0 = a.clipX(b, x0);
//        Vector2D *xh1 = a.clipX(b, x1);
//        Vector2D *yh0 = a.clipY(b, y0);
//        Vector2D *yh1 = a.clipY(b, y1);
//
//        if (!containsX(*xh0)) {
//            delete xh0;      
//            xh0 = nullptr;
//        }
//        if (!containsX(*xh1)) {
//            delete xh1;          
//            xh1 = nullptr;
//        }
//        if (!containsY(*yh0)) {
//            delete yh0;          
//            yh0 = nullptr;
//        }
//        if (!containsY(*yh1)) {
//            delete yh1;            
//            yh1 = nullptr;
//        }
//
//        Vector2D *closest = nullptr;
//        if (xh0 != NULL && (closest == NULL || a.distanceToSqr(xh0) < a->distanceToSqr(closest))) closest = xh0;
//        if (xh1 != NULL && (closest == NULL || a.distanceToSqr(xh1) < a->distanceToSqr(closest))) closest = xh1;
//        if (yh0 != NULL && (closest == NULL || a.distanceToSqr(yh0) < a->distanceToSqr(closest))) closest = yh0;
//        if (yh1 != NULL && (closest == NULL || a.distanceToSqr(yh1) < a->distanceToSqr(closest))) closest = yh1;
//        
//        if (closest == NULL) return NULL;
//        int face = -1;
//        if (closest == xh0) face = 4;
//        if (closest == xh1) face = 5;
//        if (closest == yh0) face = 0;
//        if (closest == yh1) face = 1;
//        if (closest == zh0) face = 2;
//        if (closest == zh1) face = 3;
//        return new HitResult(0, 0, 0, face, closest);
//    }


        bool AABB::intersects_face_x(const Vector2D& v) const {
            return v.y >= y0 && v.y <= y1;
        }

        bool AABB::intersects_face_y(const Vector2D& v) const {
            return v.x >= x0 && v.x <= x1;
        }

        void AABB::set(const AABB& b) {
            this->x0 = b.x0;
            this->y0 = b.y0;

            this->x1 = b.x1;
            this->y1 = b.y1;
        }
    }
}