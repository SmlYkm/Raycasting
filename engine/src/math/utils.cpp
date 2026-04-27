#include "math/utils.hpp"

namespace engine {
    namespace math {
        int min_int() {                     // Black magic bit hacking wizardry
            unsigned int num = 69;          // XX...X1 (Could be any ODD number, I chose 69 because of Apollo11) (Doesn't have to be unsigned, just using it for consistency with find_max)
            int shift = sizeof(int) * 8 - 1;
            num = num << shift;             // 10...00
            return num;
        }

        int max_int() {                     // Black magic bit hacking wizardry again
            unsigned int num = 69;          // 0xXXXX (Could be any number, I chose 69 because of Apollo 11) (Unsigned so the compiler doesn't fuck up)
            num = num ^ num;                // 0xXXXX -> 0x0000 (A xor A = 0x0000)
            num = ~num;                     // 0xFFFF
            num = num >> 1;                 // 0111111...
            return num;
        }
         
        unsigned int factorial(const unsigned int n) {
            unsigned int result = 1;
            for (int i = n; i > 1; --i) {
                result *= i;
            }
            return result;
        }

        int pow_int(const int base, const unsigned int exp) {
            unsigned int result = 1;
            for (unsigned int i = 0; i < exp; ++i) {
                result *= base;
            }
            return result;
        }

        int gcd(int a, int b) {
            if (a == 0) {
                return b;
            }
            if (b == 0) {
                return a;
            }

            int k = 0;
            for (k = 0; ((a | b) & 1) == 0; ++k) {
                a >>= 1;
                b >>= 1;
            }

            while ((a & 1) == 0) {
                a >>= 1;
            }

            do {
                while ((b & 1) == 0) {
                    b >>= 1;
                }
                if (a > b) {
                    const int temp = b;
                    b = a;
                    a = temp;
                }
                b = (b - a);
            } while (b != 0);

            return a << k;
        }

        unsigned int estimate_sqrt_int(const unsigned int n, const short unsigned int n_recursions) {
            if (n == 0 || n == 1) {
                return n;
            }
            unsigned int guess = n / 2;
            for (short unsigned int i = 0; i < n_recursions; ++i) { 
                if (guess * guess == n){
                    return guess;
                }
                guess = (n/guess + guess) / 2;
            }
            return guess;
        }

        bool mul_will_overflow(int a, int b) {
            if (a == 0 || b == 0) {
                return false;
            }
            // We check against max_int() / b. 
            // We have to be careful about signs, assuming a and b are positive for this snippet:
            const int maxint = max_int();
            if (a > 0 && b > 0 && a > (maxint / b)) {
                return true; 
            }            
            return false;
        }
    }
}