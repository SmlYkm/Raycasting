#include "math/FixedPointInt.hpp"
#include "math/utils.hpp"

namespace engine {
    namespace math {
        FixedPointInt::FixedPointInt(const int number, const bool human_readable)
            : bits_m(number) {
            if (human_readable) {
                set(number);
            }
        }

        FixedPointInt::FixedPointInt(const FixedPointInt& other) 
            : bits_m(other.bits_m) {
        }

        FixedPointInt::~FixedPointInt() {
        }

        int FixedPointInt::n_post_point_bits() {
            static int n_post_point_bits_m = sizeof(int) * 8 / 2;
            return n_post_point_bits_m;
        }

        const FixedPointInt FixedPointInt::max_factorial_n() {
            static FixedPointInt max_factorial_n_m = n_factorial_overflows_at();
            return max_factorial_n_m;
        }

        const FixedPointInt FixedPointInt::min() {
            static FixedPointInt min_m = min_FixedPointInt();
            return min_m;
        }

        const FixedPointInt FixedPointInt::max() {
            static FixedPointInt max_m = max_FixedPointInt();
            return max_m;
        }

        const FixedPointInt FixedPointInt::pi() {
            static FixedPointInt pi_m = compute_pi();
            return pi_m;
        }



        const FixedPointInt FixedPointInt::max_FixedPointInt() {
            return FixedPointInt(max_int(), false);
        }

        const FixedPointInt FixedPointInt::min_FixedPointInt() {
            return FixedPointInt(min_int(), false);
        }

        const FixedPointInt FixedPointInt::n_factorial_overflows_at() {
            int n = 1;
            int current = 1 << n_post_point_bits();
            
            while (!mul_will_overflow(current, n + 1)) {
                ++n;
                current *= n;
            }
            return FixedPointInt(n, true);
        }

        const FixedPointInt FixedPointInt::compute_pi() {
            // 355 / 113 is a famous rational approximation of Pi.
            // By using the 'true' constructor, the class handles the bit-shifting 
            // dynamically based on the platform's integer size.
            FixedPointInt numerator(355, true);
            FixedPointInt denominator(113, true);
            
            return numerator / denominator;
        }

        // Core Conversions
        int FixedPointInt::value() const {
            return bits_m;
        }

        void FixedPointInt::set(const int number) {
            bits_m = number << n_post_point_bits();
        }

        int FixedPointInt::to_int() const {
            return bits_m >> n_post_point_bits();
        }

        // Basic Math
        FixedPointInt FixedPointInt::operator+(const FixedPointInt &other) const {
            return FixedPointInt(bits_m + other.bits_m, false);
        }

        FixedPointInt FixedPointInt::operator-(const FixedPointInt &other) const {
            return FixedPointInt(bits_m - other.bits_m, false);
        }

        FixedPointInt FixedPointInt::operator*(const FixedPointInt &other) const {
            long long temp = (long long)(bits_m) * (long long)(other.bits_m);
            return FixedPointInt((int)(temp >> n_post_point_bits()), false);
        }

        FixedPointInt FixedPointInt::operator/(const FixedPointInt &other) const {
            long long temp = (long long)(bits_m) << n_post_point_bits();
            return FixedPointInt((int)(temp / other.bits_m), false);
        }

        // Assignment Operators
        FixedPointInt& FixedPointInt::operator=(const FixedPointInt &other) {
            bits_m = other.bits_m;
            return *this;
        }

        FixedPointInt& FixedPointInt::operator=(const int number) {
            set(number);
            return *this;
        }

        FixedPointInt& FixedPointInt::operator+=(const FixedPointInt &other) {
            bits_m += other.bits_m;
            return *this;
        }

        FixedPointInt& FixedPointInt::operator-=(const FixedPointInt &other) {
            bits_m -= other.bits_m;
            return *this;
        }

        FixedPointInt& FixedPointInt::operator*=(const FixedPointInt &other) {
            *this = *this * other; 
            return *this;
        }

        FixedPointInt& FixedPointInt::operator/=(const FixedPointInt &other) {
            *this = *this / other;
            return *this;
        }

        FixedPointInt& FixedPointInt::operator++() {  // Pre
            bits_m += (1 << n_post_point_bits()); 
            return *this;
        }

        FixedPointInt FixedPointInt::operator++(int) {  // Post
            FixedPointInt temp(*this);            
            bits_m += (1 << n_post_point_bits());  
            return temp;                          
        }

        FixedPointInt& FixedPointInt::operator--() {  // Pre
            bits_m -= (1 << n_post_point_bits());
            return *this;
        }

        FixedPointInt FixedPointInt::operator--(int) {  // Post
            FixedPointInt temp(*this);
            bits_m -= (1 << n_post_point_bits());
            return temp;
        }

        // Logical Operators 
        bool FixedPointInt::operator==(const FixedPointInt &other) const {
            return bits_m == other.bits_m;
        }

        bool FixedPointInt::operator==(const int number) const {
            return bits_m == (number << n_post_point_bits());
        }

        bool operator==(const int number, const FixedPointInt &other) {
            return other == number;
        }

        bool FixedPointInt::operator!=(const FixedPointInt &other) const {
            return bits_m != other.bits_m;
        }

        bool FixedPointInt::operator!=(const int number) const {
            return bits_m != (number << n_post_point_bits());
        }

        bool operator!=(const int number, const FixedPointInt &other) {
            return other != number;
        }

        bool FixedPointInt::operator<(const FixedPointInt &other) const {
            return bits_m < other.bits_m;
        }

        bool FixedPointInt::operator<(const int number) const {
            return bits_m < (number << n_post_point_bits());
        }

        bool operator<(const int number, const FixedPointInt &other) {
            return other > number;
        }

        bool FixedPointInt::operator>(const FixedPointInt &other) const {
            return bits_m > other.bits_m;
        }

        bool FixedPointInt::operator>(const int number) const {
            return bits_m > (number << n_post_point_bits());
        }

        bool operator>(const int number, const FixedPointInt &other) {
            return other < number;
        }

        bool FixedPointInt::operator<=(const FixedPointInt &other) const {
            return bits_m <= other.bits_m;
        }

        bool FixedPointInt::operator<=(const int number) const {
            return bits_m <= (number << n_post_point_bits());
        }

        bool operator<=(const int number, const FixedPointInt &other) {
            return other >= number;
        }

        bool FixedPointInt::operator>=(const FixedPointInt &other) const {
            return bits_m >= other.bits_m;
        }

        bool FixedPointInt::operator>=(const int number) const {
            return bits_m >= (number << n_post_point_bits());
        }

        bool operator>=(const int number, const FixedPointInt &other) {
            return other <= number;
        }

        FixedPointInt FixedPointInt::pow(unsigned int exp) {
            FixedPointInt result(1, true); // Start at 1.0
            FixedPointInt base(*this);     // Copy the base
            
            while (exp > 0) {
                // If the exponent is odd, multiply the result by the current base
                if (exp % 2 == 1) {
                    result *= base;
                }
                // Square the base and cut the exponent in half
                base *= base;
                exp /= 2;
            }
            return result;
        }

        FixedPointInt FixedPointInt::sqrt(const short unsigned int n_recursions) {
            // We assume the person using this function is responsible and
            // knows that n must be positive
            if (*this == 0 || *this == 1) {
                 return *this;
            }
            FixedPointInt guess = *this / 2;
            for (short unsigned int i = 0; i < n_recursions; ++i) { 
                if (guess * guess == *this){
                    return guess;
                }
                guess = (*this / guess + guess) / 2;
            }
            return guess;
        }

        FixedPointInt FixedPointInt::factorial() {
            if (*this > max_factorial_n()) {
                return FixedPointInt(-1, true);
            }
            int n = 1;
            for (int i = bits_m >> n_post_point_bits(); i > 1; --i) {
                n *= i;
            }
            return FixedPointInt(n, true);
        }

        // Returns the whole number, chopping off the fraction. (e.g., 5.9 becomes 5.0)
        FixedPointInt FixedPointInt::floor() const {
            // 0xFFFF0000 keeps the top 16 bits (whole) and zeroes the bottom 16 (fraction)
            return FixedPointInt(bits_m & 0xFFFF0000, false);
        }

        // Ceiling is just floor() + 1.0 (if there is a fraction)
        FixedPointInt FixedPointInt::ceil() const {
            if ((bits_m & 0x0000FFFF) == 0) {
                return *this; // Already a whole number
            }
            return floor() + FixedPointInt(1, true);
        }
    }
}

