#pragma once

#include "FixedPointInt32.hpp"

namespace engine {
    namespace math {
        
        class Vector2D {
        public:
            FixedPointInt32 x;
            FixedPointInt32 y;
            
        public:
            Vector2D(FixedPointInt32 x_p, FixedPointInt32 y_p) : 
                x(x_p), 
                y(y_p) {
            }

            Vector2D(const Vector2D& other)  : 
                x(other.x), 
                y(other.y) {
            }

            Vector2D() : 
                x(0) , 
                y(0) {
            }
            
            ~Vector2D() {
            }

            // Vector2D *clipX(const Vector2D& b, FixedPointInt32 xt) const {  
            //     FixedPointInt32 xd = b.x - x;
            //     FixedPointInt32 yd = b.y - y;
// 
            //     if (xd * xd < FixedPointInt32::eps()) 
            //         return nullptr;
// 
            //     FixedPointInt32 d = (xt - x) / xd;
            //     if (d < 0 || d > 1) 
            //         return nullptr;
            //     
            //     return new Vector2D(x+xd*d, y+yd*d);
            // }

            //Vector2D *clipY(const Vector2D& b, FixedPointInt32 yt) const{  
            //    FixedPointInt32 yd = b.y - y;
//
            //    if (yd * yd < FixedPointInt32::eps()) 
            //        return nullptr;
//
            //    FixedPointInt32 d = (yt - y) / yd;
            //    if (d < 0 || d > 1) 
            //        return nullptr;
            //    return new Vector2D(x+xd*d, y+yd*d);
            //}

            Vector2D get_orthogonal() const { 
                // Using 0 - x to safely invert the number without needing a unary operator
                return Vector2D(y, FixedPointInt32(0) - x); 
            }

            FixedPointInt32 length_squared() const { 
                return (x * x) + (y * y); 
            }

            FixedPointInt32 length() const { 
                return length_squared().sqrt(); 
            }

            void normalize() {
                FixedPointInt32 len = length();
                if (len != 0) {
                    x /= len;
                    y /= len;
                }
            }

            Vector2D operator+(const Vector2D& other) const {
                return Vector2D(x + other.x, y + other.y);
            }
            
            Vector2D operator-(const Vector2D& other) const {
                return Vector2D(x - other.x, y - other.y);
            }

            // Scalar Multiplication
            Vector2D operator*(FixedPointInt32 scalar) const {
                return Vector2D(x * scalar, y * scalar);
            }

            // Dot Product
            FixedPointInt32 operator*(const Vector2D& other) const {
                return (x * other.x) + (y * other.y);
            }
            
            // Scalar Division
            Vector2D operator/(FixedPointInt32 scalar) const {
                return Vector2D(x / scalar, y / scalar);
            }
            
            Vector2D& operator=(const Vector2D& other) {
                x = other.x;
                y = other.y;
                return *this;
            }

            Vector2D& operator+=(const Vector2D& other) {
                x += other.x;
                y += other.y;
                return *this;
            }

            Vector2D& operator-=(const Vector2D& other) {
                x -= other.x;
                y -= other.y;
                return *this;
            }

            Vector2D& operator*=(FixedPointInt32 scalar) {
                x *= scalar;
                y *= scalar;
                return *this;
            }

            Vector2D& operator/=(FixedPointInt32 scalar) {
                x /= scalar;
                y /= scalar;
                return *this;
            }

            bool operator==(const Vector2D& other) const {
                return x == other.x && y == other.y;
            }

            bool operator!=(const Vector2D& other) const {
                return x != other.x || y != other.y;
            }
        };

        // Global scalar multiplication: scalar * Vector
        // 'inline' prevents linker errors when included in multiple translation units!
        inline Vector2D operator*(FixedPointInt32 scalar, const Vector2D& vec) {
            return vec * scalar;
        }

        // Convenience overload: Allows you to type `5 * vec` directly
        inline Vector2D operator*(int scalar, const Vector2D& vec) {
            return vec * FixedPointInt32(scalar, true);
        }
    }
}