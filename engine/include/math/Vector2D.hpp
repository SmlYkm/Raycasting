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

            Vector2D get_orthogonal() const { 
                return Vector2D(y, -x); 
            }

            int64_t length_squared() const {                 
                int64_t this_x  = (int64_t) x.get();
                int64_t this_y  = (int64_t) y.get();


                return this_x*this_x + this_y*this_y;
            }

            // FixedPointInt32 length() const { 
            //     return length_squared().sqrt(); 
            // }

            // void normalize() {
            //     int64_t this_x  = (int64_t) x.get();
            //     int64_t this_y  = (int64_t) y.get();
            //     int64_t len     = length();
            //     if (len != 0) {
            //         x /= len;
            //         y /= len;
            //     }
            // }

            Vector2D operator+(const Vector2D& other) const {
                return Vector2D(x + other.x, y + other.y);
            }
            
            Vector2D operator-(const Vector2D& other) const {
                return Vector2D(x - other.x, y - other.y);
            }

            Vector2D operator-() {
                return Vector2D(-x, -y);
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

            bool operator<(const Vector2D& other) const {
                int64_t this_x  = (int64_t) x.get();
                int64_t this_y  = (int64_t) y.get();
                int64_t other_x = (int64_t) other.x.get();
                int64_t other_y = (int64_t) other.y.get();

                return (this_x*this_x + this_y*this_y < other_x*other_x +other_y*other_y );
            }

            bool operator<=(const Vector2D& other) const {
                return length_squared() <= other.length_squared();
            }

            bool operator>(const Vector2D& other) const {
                return length_squared() > other.length_squared();
            }

            bool operator>=(const Vector2D& other) const {
                return length_squared() >= other.length_squared();
            }

            friend std::ostream& operator<<(std::ostream &out, const Vector2D& n) {  // cout overload
                out << "(" << n.x << ", " << n.y << ")";
                return out;                
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