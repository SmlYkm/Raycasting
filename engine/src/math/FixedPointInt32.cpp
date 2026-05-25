#include "math/FixedPointInt32.hpp"
#include "math/utils.hpp"

#include <stdexcept>

namespace engine {
    namespace math {
        FixedPointInt32::FixedPointInt32(const int32_t number, const bool human_readable) : 
            bits_m(number) {
            if (human_readable)
                set(number);
        }

        FixedPointInt32::FixedPointInt32(int32_t number, const int32_t comma_pos) :
            bits_m(0) {  // fallback
            bool is_negative = number < 0;
            if (is_negative)  // For simplicity, treating everything as postive
                number *= -1; // If it is negative, just multiply by -1 at the end

            int32_t  multiplier  = 1;
            for (int32_t i = 0; i < comma_pos; ++i) 
                multiplier  *= 10;

            int32_t whole = number / multiplier;  
            int32_t frac  = number % multiplier;

            frac = ((uint64_t)frac << 16) / multiplier;
            uint32_t temp_bits = (whole << 16) | (frac & 0x0000FFFF);

            bits_m = temp_bits;
            if (is_negative)
                bits_m *= -1;
        }

        FixedPointInt32::FixedPointInt32(const FixedPointInt32& other) 
            : bits_m(other.bits_m) {
        }

        FixedPointInt32::~FixedPointInt32() {
        }

        int32_t FixedPointInt32::n_post_point_bits() {
            return 16;
        }

        const FixedPointInt32 FixedPointInt32::max_factorial_n() {
            static FixedPointInt32 max_factorial_n_m = n_factorial_overflows_at();
            return max_factorial_n_m;
        }

        const FixedPointInt32 FixedPointInt32::min() {
            static FixedPointInt32 min_m = min_FixedPointInt32();
            return min_m;
        }

        const FixedPointInt32 FixedPointInt32::max() {
            static FixedPointInt32 max_m = max_FixedPointInt32();
            return max_m;
        }

        const FixedPointInt32 FixedPointInt32::pi() {
            static FixedPointInt32 pi_m = compute_pi();
            return pi_m;
        }



        const FixedPointInt32 FixedPointInt32::max_FixedPointInt32() {
            return FixedPointInt32(max_int(), false);
        }

        const FixedPointInt32 FixedPointInt32::min_FixedPointInt32() {
            return FixedPointInt32(min_int(), false);
        }

        const FixedPointInt32 FixedPointInt32::n_factorial_overflows_at() {
            return FixedPointInt32(8);
        }

        const FixedPointInt32 FixedPointInt32::compute_pi() {
            // 355 / 113 ~= PI
            FixedPointInt32 numerator(355, true);
            FixedPointInt32 denominator(113, true);
            
            return numerator / denominator;
        }

        int32_t FixedPointInt32::get() const {
            return bits_m;
        }

        void FixedPointInt32::set(const int32_t number) {
            int64_t temp = (int64_t)number;
            bits_m = (int32_t)(temp << 16);
        }

        int32_t FixedPointInt32::get_int() const {
            bool    is_negative = bits_m < 0;
            int32_t temp        = bits_m;
            
            if (is_negative)  // treat as positive and just multiply by -1 in the end
                temp *= -1;

            temp = temp >> 16;
            return is_negative ? temp*-1 : temp;
        }

        int32_t FixedPointInt32::get_frac() const {
            bool    is_negative = bits_m < 0;
            int32_t temp        = bits_m;

            if (is_negative)  // Treat as positive, same as above
                temp *= -1;

            temp = temp & 0x0000FFFF;
            // while ((temp & 0x00000001) != 0x00000001) { wrong
            //     temp = temp >> 1;
            // }
            return is_negative ? (temp*-1) : temp;
        }


        // Basic Math
        FixedPointInt32 FixedPointInt32::operator+(const FixedPointInt32 &other) const {
            return FixedPointInt32(bits_m + other.bits_m, false);
        }

        FixedPointInt32 FixedPointInt32::operator+(const int32_t number) const {
            return *this + FixedPointInt32(number);
        }

        FixedPointInt32 operator+(const int32_t number, const FixedPointInt32 &other) {
            return FixedPointInt32(number) + other;
        }


        FixedPointInt32 FixedPointInt32::operator-(const FixedPointInt32 &other) const {
            return FixedPointInt32(bits_m - other.bits_m, false);
        }

        FixedPointInt32 FixedPointInt32::operator-(const int32_t number) const {
            return *this - FixedPointInt32(number);
        }

        FixedPointInt32 operator-(const int32_t number, const FixedPointInt32 &other) {
            return FixedPointInt32(number) - other;
        }

        FixedPointInt32 FixedPointInt32::operator-() const {
            return FixedPointInt32(-bits_m);
        }

        FixedPointInt32 FixedPointInt32::operator*(const FixedPointInt32 &other) const {
            int64_t temp = (int64_t)(bits_m) * (int64_t)(other.bits_m);
            return FixedPointInt32((int32_t)(temp >> 16), false);
        }

        FixedPointInt32 FixedPointInt32::operator*(const int32_t number) const {
            return *this * FixedPointInt32(number);
        }

        FixedPointInt32 operator*(const int32_t number, const FixedPointInt32 &other) {
            return FixedPointInt32(number) * other;
        }

        FixedPointInt32 FixedPointInt32::operator/(const FixedPointInt32 &other) const {
            if (other.bits_m == 0)
                throw std::runtime_error("Division by 0!\n");

            int64_t temp = (int64_t)(bits_m) << 16;
            return FixedPointInt32((int32_t)(temp / other.bits_m), false);
        }

        FixedPointInt32 FixedPointInt32::operator/(const int32_t number) const {
            return *this / FixedPointInt32(number);
        }

        FixedPointInt32 operator/(const int32_t number, const FixedPointInt32 &other) {
            return FixedPointInt32(number) / other;
        }

        // Assignment Operators
        FixedPointInt32& FixedPointInt32::operator=(const FixedPointInt32 &other) {
            bits_m = other.bits_m;
            return *this;
        }

        FixedPointInt32& FixedPointInt32::operator=(const int32_t number) {
            set(number);
            return *this;
        }

        FixedPointInt32& FixedPointInt32::operator+=(const FixedPointInt32 &other) {
            bits_m += other.bits_m;
            return *this;
        }

        FixedPointInt32& FixedPointInt32::operator+=(const int32_t number) {
            return *this += FixedPointInt32(number);
        }

        FixedPointInt32 operator+=(const int32_t number, const FixedPointInt32 &other) {
            return FixedPointInt32(number) + other;
        }


        FixedPointInt32& FixedPointInt32::operator-=(const FixedPointInt32 &other) {
            bits_m -= other.bits_m;
            return *this;
        }

        FixedPointInt32& FixedPointInt32::operator-=(const int32_t number) {
            return *this -= FixedPointInt32(number);
        }

        FixedPointInt32 operator-=(const int32_t number, const FixedPointInt32 &other) {
            return FixedPointInt32(number) - other;
        }

        FixedPointInt32& FixedPointInt32::operator*=(const FixedPointInt32 &other) {
            *this = *this * other; 
            return *this;
        }

        FixedPointInt32& FixedPointInt32::operator*=(const int32_t number) {
            return *this *= FixedPointInt32(number);
        }

        FixedPointInt32 operator*=(const int32_t number, const FixedPointInt32 &other) {
            return FixedPointInt32(number) * other;
        }

        FixedPointInt32& FixedPointInt32::operator/=(const FixedPointInt32 &other) {
            if (other.bits_m == 0)
                throw std::runtime_error("Division by 0!\n");

            *this = *this / other;
            return *this;
        }

        FixedPointInt32& FixedPointInt32::operator/=(const int32_t number) {
            return *this /= FixedPointInt32(number);
        }

        FixedPointInt32 operator/=(const int32_t number, const FixedPointInt32 &other) {
            return FixedPointInt32(number) / other;
        }

        FixedPointInt32& FixedPointInt32::operator++() {  // Pre
            bits_m += int32_t(0x00010000); 
            return *this;
        }

        FixedPointInt32 FixedPointInt32::operator++(int32_t) {  // Post
            FixedPointInt32 temp(*this);            
            bits_m += int32_t(0x00010000);  
            return temp;                          
        }

        FixedPointInt32& FixedPointInt32::operator--() {  // Pre
            bits_m -= int32_t(0x00010000);  
            return *this;
        }

        FixedPointInt32 FixedPointInt32::operator--(int32_t) {  // Post
            FixedPointInt32 temp(*this);
            bits_m -= int32_t(0x00010000);  
            return temp;
        }

        // Logical Operators 
        bool FixedPointInt32::operator==(const FixedPointInt32 &other) const {
            return bits_m == other.bits_m;
        }

        bool FixedPointInt32::operator==(const int32_t number) const {
            if (bits_m & 0x0000FFFF || number & 0xFFFF0000)
                return false;

            return bits_m == (number << 16);
        }

        bool operator==(const int32_t number, const FixedPointInt32 &other) {
            return other == number;
        }

        bool FixedPointInt32::operator!=(const FixedPointInt32 &other) const {
            return bits_m != other.bits_m;
        }

        bool FixedPointInt32::operator!=(const int32_t number) const {
            if (bits_m & 0x0000FFFF || number & 0xFFFF0000)
                return true;

            return bits_m != (number << 16);
        }

        bool operator!=(const int32_t number, const FixedPointInt32 &other) {
            return other != number;
        }

        bool FixedPointInt32::operator<(const FixedPointInt32 &other) const {
            return bits_m < other.bits_m;
        }

        bool FixedPointInt32::operator<(const int32_t number) const {
            return bits_m < (number << 16);
        }

        bool operator<(const int32_t number, const FixedPointInt32 &other) {
            return other > number;
        }

        bool FixedPointInt32::operator>(const FixedPointInt32 &other) const {
            return bits_m > other.bits_m;
        }

        bool FixedPointInt32::operator>(const int32_t number) const {
            return bits_m > (number << 16);
        }

        bool operator>(const int32_t number, const FixedPointInt32 &other) {
            return other < number;
        }

        bool FixedPointInt32::operator<=(const FixedPointInt32 &other) const {
            return bits_m <= other.bits_m;
        }

        bool FixedPointInt32::operator<=(const int32_t number) const {
            return bits_m <= (number << 16);
        }

        bool operator<=(const int32_t number, const FixedPointInt32 &other) {
            return other >= number;
        }

        bool FixedPointInt32::operator>=(const FixedPointInt32 &other) const {
            return bits_m >= other.bits_m;
        }

        bool FixedPointInt32::operator>=(const int32_t number) const {
            return bits_m >= (number << 16);
        }

        bool operator>=(const int32_t number, const FixedPointInt32 &other) {
            return other <= number;
        }

        FixedPointInt32 FixedPointInt32::pow(uint16_t exp) {
            FixedPointInt32 result(1, true); // Start at 1.0
            FixedPointInt32 base(*this);     // Copy the base
            
            while (exp > 0) {
                if (exp % 2 == 1)  // If the exponent is odd, multiply the result by the current base
                    result *= base;
                
                base *= base;  // Square the base and cut the exponent in half
                exp  /= 2;
            }
            return result;
        }

        FixedPointInt32 FixedPointInt32::sqrt(uint16_t n_recursions) {
            if (*this < 0)
                throw std::runtime_error("SQRT of negative number!\n");

            if (*this == 0 || *this == 1)
                 return *this;

            FixedPointInt32 guess = *this / 2;
            for (uint16_t i = 0; i < n_recursions; ++i) { 
                if (guess * guess == *this)
                    return guess;

                guess = (*this / guess + guess) / 2;
            }
            return guess;
        }

        FixedPointInt32 FixedPointInt32::factorial() {
            if (*this > max_factorial_n())
                throw std::runtime_error("Overflow in factorial function!\n");

            int32_t n = 1;
            for (int32_t i = bits_m >> 16; i > 1; --i)
                n *= i;

            return FixedPointInt32(n, true);
        }

        FixedPointInt32 FixedPointInt32::floor() const {
            return FixedPointInt32(bits_m & 0xFFFF0000, false);
        }

        // Ceiling is just floor() + 1.0 (if there is a fraction)
        FixedPointInt32 FixedPointInt32::ceil() const {
            if ((bits_m & 0x0000FFFF) == 0)
                return *this;

            return floor() + FixedPointInt32(0x00010000, false);
        }

        std::ostream& operator<<(std::ostream& out, const FixedPointInt32& n) {
            bool is_negative = n < 0;

            int32_t whole = n.get_int();
            int32_t frac  = n.get_frac();

            if (is_negative) {
                frac  *= -1;
                whole *= -1;
                out << "-";
            }

            frac = (int32_t) (
                ((uint64_t)frac * 10000) >> 16
            );

            out << whole << ".";
            if (frac < 1000) 
                out << "0";
            if (frac < 100)  
                out << "0";
            if (frac < 10)   
                out << "0";
            out << frac;
            return out;
        }
    }
}