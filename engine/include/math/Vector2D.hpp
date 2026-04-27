#pragma once

#include "FixedPointInt.hpp"

namespace engine {
    namespace math {
        
        class Vector2D {
        public:
            FixedPointInt x;
            FixedPointInt y;
            
        public:
            Vector2D(FixedPointInt x_p, FixedPointInt y_p) 
                : x(x_p)
                , y(y_p) {
            }

            Vector2D(const Vector2D& other) 
                : x(other.x)
                , y(other.y) {
            }

            Vector2D() 
                : x(0) 
                , y(0) {
            }
            
            ~Vector2D() {
            }

            Vector2D get_orthogonal() const { 
                // Using 0 - x to safely invert the number without needing a unary operator
                return Vector2D(y, FixedPointInt(0) - x); 
            }

            FixedPointInt length_squared() const { 
                return (x * x) + (y * y); 
            }

            FixedPointInt length() const { 
                return length_squared().sqrt(); 
            }

            void normalize() {
                FixedPointInt len = length();
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
            Vector2D operator*(FixedPointInt scalar) const {
                return Vector2D(x * scalar, y * scalar);
            }

            // Dot Product
            FixedPointInt operator*(const Vector2D& other) const {
                return (x * other.x) + (y * other.y);
            }
            
            // Scalar Division
            Vector2D operator/(FixedPointInt scalar) const {
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

            Vector2D& operator*=(FixedPointInt scalar) {
                x *= scalar;
                y *= scalar;
                return *this;
            }

            Vector2D& operator/=(FixedPointInt scalar) {
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
        inline Vector2D operator*(FixedPointInt scalar, const Vector2D& vec) {
            return vec * scalar;
        }

        // Convenience overload: Allows you to type `5 * vec` directly
        inline Vector2D operator*(int scalar, const Vector2D& vec) {
            return vec * FixedPointInt(scalar, true);
        }
    }
}