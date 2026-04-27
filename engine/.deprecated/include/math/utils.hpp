#pragma once

#include "Fraction.hpp"

namespace engine {
    namespace math {
        int max_int();  // Used to find max/min int value without stdlib or external dependencies
        int min_int();  // Used to find max/min int value without stdlib or external dependencies
    
        int factorial(const int n);

        int pow(const int base, const int exp);  // Power function, takes int returns int

        Fraction pow_frac(const int base, const int exp);        // Power function, takes int or fraction returns fraction        
        Fraction pow_frac(const Fraction& base, const int exp);  // Power function, takes int or fraction returns fraction

        int gcd(const int a, const int b);  // Greatest common divisor of two numbers

        Fraction estimate_sqrt(const Fraction& n,const Fraction& error = Fraction(1, 10), const short unsigned int n_recursions = 16);  // Square root, takes fraction or int, and precision (number of iterations of Newton's algorithm)
        Fraction estimate_sqrt(const int n, const Fraction& error = Fraction(1, 10), const short unsigned int n_recursions = 16);       // Square root, takes fraction or int, and precision (number of iterations of Newton's algorithm)   
        
        // Estimates PI using the infinite sided polygon method, 
        // takes error (how distant it is from the real number)
        // the smaller the error, the more precise it is, but may cause overflows
        Fraction estimate_pi(const Fraction& error = Fraction(1, 10), const short unsigned int n_recursions = 16);
        
        // Used to create an "infinite" sided polygon, used to estimate PI
        // You probably won't find any other utility for this function,
        // still, I'm not limiting it's scope, perhaps it'll come handy sometime...
        Fraction double_polygon_n_sides(const Fraction& l, const Fraction& error = Fraction(1, 10), const short unsigned int n_recursions = 16);  
    }  // namespace math
}  // namespace engine