#pragma once

namespace engine {
    namespace math {
        class FixedPointInt {
        private:
            int bits_m;

        public:
            // Constructors
            FixedPointInt(const int number = 0, const bool human_readable = true);
            FixedPointInt(const FixedPointInt& other);
            ~FixedPointInt();

        public:
            static int n_post_point_bits(); // Usually 16
            static const FixedPointInt max_factorial_n();
            static const FixedPointInt max();
            static const FixedPointInt min();
            static const FixedPointInt pi();

        private:
            static const FixedPointInt max_FixedPointInt();
            static const FixedPointInt min_FixedPointInt();
            static const FixedPointInt n_factorial_overflows_at();
            static const FixedPointInt compute_pi();

        public:
            // Accessors
            int value() const;
            void set(const int number);
            int to_int() const;

        public:
            // Mathematical Operators
            FixedPointInt operator+(const FixedPointInt &other) const;
            FixedPointInt operator-(const FixedPointInt &other) const;
            FixedPointInt operator*(const FixedPointInt &other) const;
            FixedPointInt operator/(const FixedPointInt &other) const;
            
            FixedPointInt& operator=(const FixedPointInt &other);
            FixedPointInt& operator=(const int number);

            FixedPointInt& operator+=(const FixedPointInt &other);
            FixedPointInt& operator-=(const FixedPointInt &other);
            FixedPointInt& operator*=(const FixedPointInt &other);
            FixedPointInt& operator/=(const FixedPointInt &other);

            FixedPointInt& operator++();       
            FixedPointInt operator++(int);     
            FixedPointInt& operator--();       
            FixedPointInt operator--(int);     

            // Logical operators
            bool operator==(const FixedPointInt &other) const;
            bool operator==(const int number) const;
            friend bool operator==(const int number, const FixedPointInt &other);

            bool operator!=(const FixedPointInt &other) const;
            bool operator!=(const int number) const;
            friend bool operator!=(const int number, const FixedPointInt &other);

            bool operator<(const FixedPointInt &other) const;
            bool operator<(const int number) const;
            friend bool operator<(const int number, const FixedPointInt &other);

            bool operator>(const FixedPointInt &other) const;
            bool operator>(const int number) const;
            friend bool operator>(const int number, const FixedPointInt &other);

            bool operator<=(const FixedPointInt &other) const;
            bool operator<=(const int number) const;
            friend bool operator<=(const int number, const FixedPointInt &other);

            bool operator>=(const FixedPointInt &other) const;
            bool operator>=(const int number) const;
            friend bool operator>=(const int number, const FixedPointInt &other);

            // Mathematical functions
            FixedPointInt pow(unsigned int exp);  // Power function, takes FixedPointInt returns FixedPointInt, overflows really fast
            FixedPointInt sqrt(const short unsigned int n_recursions = 16);
            FixedPointInt factorial();
            FixedPointInt floor() const;
            FixedPointInt ceil() const;
        };
    }
}
