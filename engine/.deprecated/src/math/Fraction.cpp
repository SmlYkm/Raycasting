#include "math/Fraction.hpp"
#include "math/utils.hpp"

namespace engine {
    namespace math {
        const int Fraction::min_int(math::min_int());
        const int Fraction::max_int(math::max_int());

        Fraction::Fraction(const int top, const int bottom)
            : top_m(top), bottom_m(bottom) {
            // Normalize: If the bottom is negative, move the negative sign to the top
            if (bottom_m < 0) {
                top_m = -top_m;
                bottom_m = -bottom_m;
            }
        }

        Fraction::Fraction(const Fraction& other) 
            : top_m(other.top_m), bottom_m(other.bottom_m) {
        }

        Fraction::~Fraction() {
        }

        const Fraction Fraction::operator+(const Fraction &other) const {
            return Fraction(
                top_m * other.bottom_m + other.top_m * bottom_m,
                other.bottom_m * bottom_m
            );
        }

        const Fraction Fraction::operator+(const int number) const {
            return Fraction(top_m + number * bottom_m, bottom_m);
        }

        const Fraction operator+(const int number, const Fraction &other) {
            return Fraction(other.top_m + number * other.bottom_m, other.bottom_m);
        }

        const Fraction Fraction::operator-(const Fraction &other) const {
            return Fraction(
                top_m * other.bottom_m - other.top_m * bottom_m,
                other.bottom_m * bottom_m
            );
        }

        const Fraction Fraction::operator-(const int number) const {
            return Fraction(top_m - number * bottom_m, bottom_m);
        }

        const Fraction operator-(const int number, const Fraction &other) {
            return Fraction(number * other.bottom_m - other.top_m, other.bottom_m);
        }

        const Fraction Fraction::operator*(const Fraction &other) const {
            return Fraction(top_m * other.top_m, other.bottom_m * bottom_m);
        }

        const Fraction Fraction::operator*(const int number) const {
            return Fraction(top_m * number, bottom_m);
        }

        const Fraction operator*(const int number, const Fraction &other) {
            return Fraction(other.top_m * number, other.bottom_m);
        }

        const Fraction Fraction::operator/(const Fraction &other) const {
            return Fraction(other.bottom_m * top_m, other.top_m * bottom_m);
        }

        const Fraction Fraction::operator/(const int number) const {
            return Fraction(top_m, number * bottom_m);
        }

        const Fraction operator/(const int number, const Fraction &other) {
            return Fraction(number * other.bottom_m, other.top_m);
        }

        Fraction& Fraction::operator=(const Fraction &other) {
            top_m = other.top_m;
            bottom_m = other.bottom_m;
            return *this;
        }

        Fraction& Fraction::operator=(const int number) {
            top_m = number;
            bottom_m = 1;
            return *this;
        }

        Fraction& Fraction::operator+=(const Fraction &other) {
            *this = *this + other; // Safely uses your + operator and constructor!
            return *this;
        }

        Fraction& Fraction::operator+=(const int number) {
            *this = *this + number;
            return *this;
        }

        Fraction& Fraction::operator-=(const Fraction &other) {
            *this = *this - other;
            return *this;
        }

        Fraction& Fraction::operator-=(const int number) {
            *this = *this - number;
            return *this;
        }

        Fraction& Fraction::operator*=(const Fraction &other) {
            *this = *this * other;
            return *this;
        }

        Fraction& Fraction::operator*=(const int number) {
            *this = *this * number;
            return *this;
        }

        Fraction& Fraction::operator/=(const Fraction &other) {
            *this = *this / other; // Now perfectly safe from negative denominators!
            return *this;
        }

        Fraction& Fraction::operator/=(const int number) {
            *this = *this / number; // Now perfectly safe!
            return *this;
        }
        // Logical operators

        bool Fraction::operator==(const Fraction &other) const {
            return (top_m * other.bottom_m == other.top_m * bottom_m);
        }

        bool Fraction::operator==(const int number) const {
            return (top_m == number * bottom_m);
        }

        bool operator==(const int number, const Fraction &other) {
            return (number * other.bottom_m == other.top_m);
        }

        bool Fraction::operator!=(const Fraction &other) const {
            return (top_m * other.bottom_m != other.top_m * bottom_m);
        }

        bool Fraction::operator!=(const int number) const {
            return (top_m != number * bottom_m);
        }

        bool operator!=(const int number, const Fraction &other) {
            return (number * other.bottom_m != other.top_m);
        }

        bool Fraction::operator<(const Fraction &other) const {
            return (top_m * other.bottom_m < other.top_m * bottom_m);
        }

        bool Fraction::operator<(const int number) const {
            return (top_m < number * bottom_m);
        }

        bool operator<(const int number, const Fraction &other) {
            return (number * other.bottom_m < other.top_m);
        }

        bool Fraction::operator>(const Fraction &other) const {
            return (top_m * other.bottom_m > other.top_m * bottom_m);
        }

        bool Fraction::operator>(const int number) const {
            return (top_m > number * bottom_m);
        }

        bool operator>(const int number, const Fraction &other) {
            return (number * other.bottom_m > other.top_m);
        }

        bool Fraction::operator<=(const Fraction &other) const {
            return (top_m * other.bottom_m <= other.top_m * bottom_m);
        }

        bool Fraction::operator<=(const int number) const {
            return (top_m <= number * bottom_m);
        }

        bool operator<=(const int number, const Fraction &other) {
            return (number * other.bottom_m <= other.top_m);
        }

        bool Fraction::operator>=(const Fraction &other) const {
            return (top_m * other.bottom_m >= other.top_m * bottom_m);
        }

        bool Fraction::operator>=(const int number) const {
            return (top_m >= number * bottom_m);
        }

        bool operator>=(const int number, const Fraction &other) {
            return (number * other.bottom_m >= other.top_m);
        }

        int Fraction::to_int() const {
            return top_m / bottom_m;
        }

        void Fraction::prevent_overflow() {
            const int top = top_m > 0 ? top_m : -top_m;
            const int bottom = bottom_m > 0 ? bottom_m : -bottom_m;
            const int frac_gcd = gcd(top, bottom);
            
            if (frac_gcd > 1) {
                top_m = top_m / frac_gcd;
                bottom_m = bottom_m / frac_gcd; 
            }
        }

        const Fraction Fraction::abs() const {
            return Fraction(
                top_m > 0 ? top_m : -top_m,
                bottom_m > 0 ? bottom_m : -bottom_m
            );
        }
    }  // namespace math
}  // namespace engine