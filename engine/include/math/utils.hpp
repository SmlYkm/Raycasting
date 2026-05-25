#pragma once

namespace engine {
    namespace math {
        int max_int();  // Used to find max/min int value, unnecessary since you can get them from stdlib, but it's fun to check out
        int min_int();  // Used to find max/min int value, unnecessary since you can get them from stdlib, but it's fun to check out

        unsigned int factorial(const unsigned int n);
        int gcd(int a, int b);  // Greatest common divisor of two numbers
        
        int pow_int(const int base, const unsigned int exp);  // Power function, takes int returns int, overflows really fast
        unsigned int estimate_sqrt_int(const unsigned int n, const short unsigned int n_recursions = 16);
        bool mul_will_overflow(int a, int b);  // Assumes a and b are positive
    }
}