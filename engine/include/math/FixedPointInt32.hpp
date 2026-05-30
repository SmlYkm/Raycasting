#pragma once

#include <stdint.h>
#include <iostream>

namespace engine {
    namespace math {
        class FixedPointInt32 {  // 16 bits before comma, 16 bits after. For now, pretty much assuming int32_t is 32 bits long and long int32_t is 64
        private:
            int32_t bits_m;


        public:
            FixedPointInt32(const int32_t number = 0, const bool human_readable = true);  // Usage: if human_readable, converts the raw bits, otherwise, just assign
            FixedPointInt32(int32_t number, const int32_t comma_pos);  // Usage: pass number = 1652 comma_pos = 2 => 16.52
            FixedPointInt32(const FixedPointInt32& other);
            ~FixedPointInt32();

        public:
            static int32_t n_post_point_bits(); // 16
            static const FixedPointInt32 max_factorial_n();
            static const FixedPointInt32 max();
            static const FixedPointInt32 min();
            static const FixedPointInt32 eps();
            static const FixedPointInt32 greater_eps();
            static const FixedPointInt32 pi();

        private:
            static const FixedPointInt32 max_FixedPointInt32();
            static const FixedPointInt32 min_FixedPointInt32();
            static const FixedPointInt32 n_factorial_overflows_at();
            static const FixedPointInt32 compute_pi();

        public:
            // Accessors
            int32_t get() const;
            void    set(const int32_t number);
            int32_t get_int() const;
            int32_t get_frac() const;

        public:
            // Mathematical Operators
            FixedPointInt32 operator+(const FixedPointInt32 &other) const;
            FixedPointInt32 operator+(const int32_t number) const;
            friend FixedPointInt32 operator+(const int32_t number, const FixedPointInt32 &other);

            FixedPointInt32 operator-(const FixedPointInt32 &other) const;
            FixedPointInt32 operator-(const int32_t number) const;
            friend FixedPointInt32 operator-(const int32_t number, const FixedPointInt32 &other);
            FixedPointInt32 operator-() const;

            FixedPointInt32 operator*(const FixedPointInt32 &other) const;
            FixedPointInt32 operator*(const int32_t number) const;
            friend FixedPointInt32 operator*(const int32_t number, const FixedPointInt32 &other);
            
            FixedPointInt32 operator/(const FixedPointInt32 &other) const;
            FixedPointInt32 operator/(const int32_t number) const;
            friend FixedPointInt32 operator/(const int32_t number, const FixedPointInt32 &other);

            FixedPointInt32& operator=(const FixedPointInt32 &other);
            FixedPointInt32& operator=(const int32_t number);

            FixedPointInt32& operator+=(const FixedPointInt32 &other);
            FixedPointInt32& operator+=(const int32_t number);
            friend FixedPointInt32 operator+=(const int32_t number, const FixedPointInt32 &other);

            FixedPointInt32& operator-=(const FixedPointInt32 &other);
            FixedPointInt32& operator-=(const int32_t number);
            friend FixedPointInt32 operator-=(const int32_t number, const FixedPointInt32 &other);

            FixedPointInt32& operator*=(const FixedPointInt32 &other);
            FixedPointInt32& operator*=(const int32_t number);
            friend FixedPointInt32 operator*=(const int32_t number, const FixedPointInt32 &other);

            FixedPointInt32& operator/=(const FixedPointInt32 &other);
            FixedPointInt32& operator/=(const int32_t number);
            friend FixedPointInt32 operator/=(const int32_t number, const FixedPointInt32 &other);

            FixedPointInt32& operator++();       
            FixedPointInt32 operator++(int32_t);     

            FixedPointInt32& operator--();       
            FixedPointInt32 operator--(int32_t);     

            // Logical operators
            bool operator==(const FixedPointInt32 &other) const;
            bool operator==(const int32_t number) const;
            friend bool operator==(const int32_t number, const FixedPointInt32 &other);

            bool operator!=(const FixedPointInt32 &other) const;
            bool operator!=(const int32_t number) const;
            friend bool operator!=(const int32_t number, const FixedPointInt32 &other);

            bool operator<(const FixedPointInt32 &other) const;
            bool operator<(const int32_t number) const;
            friend bool operator<(const int32_t number, const FixedPointInt32 &other);

            bool operator>(const FixedPointInt32 &other) const;
            bool operator>(const int32_t number) const;
            friend bool operator>(const int32_t number, const FixedPointInt32 &other);

            bool operator<=(const FixedPointInt32 &other) const;
            bool operator<=(const int32_t number) const;
            friend bool operator<=(const int32_t number, const FixedPointInt32 &other);

            bool operator>=(const FixedPointInt32 &other) const;
            bool operator>=(const int32_t number) const;
            friend bool operator>=(const int32_t number, const FixedPointInt32 &other);

            // Mathematical functions
            FixedPointInt32 pow(const uint16_t exp);  // Power function, takes FixedPointInt32 returns FixedPointInt32, overflows really fast
            FixedPointInt32 sqrt(const uint16_t n_recursions = 16);
            FixedPointInt32 factorial();
            FixedPointInt32 floor() const;
            FixedPointInt32 ceil() const;
            FixedPointInt32 abs() const;

            friend std::ostream& operator<<(std::ostream &out, const FixedPointInt32 &n);  // cout overload
        
        public:
            static bool mul_will_overflow( FixedPointInt32 a, FixedPointInt32 b);
            static bool div_will_overflow( FixedPointInt32 a, FixedPointInt32 b);
        };
    }
}
