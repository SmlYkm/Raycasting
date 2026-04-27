#include "math/utils.hpp"

namespace engine {
    namespace math {
        int min_int() {                     // Black magic bit hacking wizardry
            unsigned int num = 69;          // XX...X1 (Could be any ODD number, I chose 69 because of Apollo11) (Doesn't have to be unsigned, just using it for consistency with find_max)
            int shift = sizeof(int) * 8 - 1;
            num = num << shift;             // 10...00
            return num;
        }

        int max_int() {             // Black magic bit hacking wizardry again!
            unsigned int num = 69;  // 0xXXXX (Could be any number, I chose 69 because of Apollo11) (Unsigned so the compiler doesn't fuck up)
            num = num ^ num;        // 0xXXXX -> 0x0000 (A xor A = 0x0000)
            num = ~num;             // 0xFFFF
            num = num >> 1;         // 0111111...
            return num;
        }

        int factorial(const int n) {
            int result = 1;
            for (int i = n; i > 1; --i) {
                result *= i;
            }
            return result;
        }

        int pow(const int base, const int exp) {
            int result = 1;
            for (int i = 0; i < exp; ++i) {
                result *= base;
            }
            return result;
        }

        Fraction pow_frac(const int base, const int exp) {
            Fraction result(1, 1);
            for (int i = 0; i < exp; ++i) {
                result *= base;
            }
            return (exp > 0) ? result : Fraction(result.bottom_m, result.top_m);
        }

        Fraction pow_frac(const Fraction& base, const int exp) {
            Fraction result(1, 1);
            for (int i = 0; i < exp; ++i) {
                result *= base;
            } 
            return (exp > 0) ? result : Fraction(result.bottom_m, result.top_m);
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

        Fraction estimate_sqrt(const Fraction& n,const Fraction& error, const short unsigned int n_recursions) {
            if (n.top_m == 0) {
                return n;
            }
            Fraction error_margin = n * error;
            error_margin.prevent_overflow();
            Fraction guess = n / 2;  // Initial guess
            for (short unsigned int i = 0; i < n_recursions; ++i) { 
                Fraction guess_value = guess * guess - n;
                guess_value.prevent_overflow();

                Fraction guess_error = guess_value - n;
                guess_error.prevent_overflow();
                
                if (guess_error.abs() < error_margin) {
                    return guess;
                }
                
                Fraction temp = (n/guess);
                temp.prevent_overflow();
                guess = (temp + guess) / 2;
                guess.prevent_overflow();
            }
            return guess;
        }

        Fraction estimate_sqrt(const int n,const Fraction& error, const short unsigned int n_recursions) {
            return estimate_sqrt(Fraction(n, 1), error, n_recursions);
        }

        Fraction estimate_pi(const Fraction& error, const short unsigned int n_recursions) {
            int n = 6;         // Hexagon
            Fraction l(1, 1);  // Haxagon side length = radius
            for (int i = 0; i < n_recursions; ++i) {
                n *= 2;
                l = double_polygon_n_sides(l, error, n_recursions);
            }
            return (l * n) / 2;
        }

        Fraction double_polygon_n_sides(const Fraction& l, const Fraction& error, const short unsigned int n_recursions) {
            return estimate_sqrt(
                (2 * (1 - estimate_sqrt(1 - l*l/4))),
                error,
                n_recursions
            );
        }
    }
}