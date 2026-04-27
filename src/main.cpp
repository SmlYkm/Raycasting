#include <iostream>
#include <iomanip> // For pretty-printing
#include <string>

#include "math/FixedPointInt.hpp"
#include "math/Trig.hpp"
#include "math/utils.hpp"

// #define USE_LIST 1

using namespace engine::math;

// Helper function just for the test bench to print FixedPoint values as human-readable decimals.
// We cheat and use floats here just so we can read the terminal output easily!
void print_fp(const std::string& name, const FixedPointInt& fp) {
    // We assume 16 fractional bits for a 32-bit system (1 << 16 = 65536)
    // To get the exact decimal, we divide the raw bits by 2^16.
    float decimal_val = (float)fp.value() / 65536.0f;
    
    std::cout << std::left << std::setw(20) << name 
              << " | Int: " << std::setw(5) << fp.to_int() 
              << " | Exact: " << std::setw(10) << decimal_val 
              << " | Raw Bits: " << fp.value() << "\n";
}

int main() {
    std::cout << "=================================================\n";
    std::cout << "   FIXED POINT MATH ENGINE - DIAGNOSTIC TEST     \n";
    std::cout << "=================================================\n\n";

    // 1. Basic Initialization & Arithmetic
    std::cout << "--- 1. BASIC ARITHMETIC ---\n";
    FixedPointInt a(10, true); // 10.0
    FixedPointInt b(4, true);  // 4.0

    print_fp("A (10.0)", a);
    print_fp("B (4.0)", b);
    print_fp("Addition (A + B)", a + b);
    print_fp("Subtract (A - B)", a - b);
    print_fp("Multiply (A * B)", a * b);
    print_fp("Division (A / B)", a / b); // Should be exactly 2.5!
    std::cout << "\n";

    // 2. Advanced Math
    std::cout << "--- 2. ADVANCED MATH ---\n";
    FixedPointInt c(2, true);
    print_fp("Power (2.0 ^ 8)", c.pow(8));         // Should be 256.0

    FixedPointInt d(144, true);
    print_fp("Square Root (144)", d.sqrt());       // Should be 12.0

    FixedPointInt e(6, true);
    print_fp("Factorial (6!)", e.factorial());     // Should be 720.0
    std::cout << "\n";

    // 3. Engine Limits & Overflows
    std::cout << "--- 3. ENGINE LIMITS ---\n";
    print_fp("Max Positive Value", FixedPointInt::max());
    print_fp("Min Negative Value", FixedPointInt::min());
    
    // Notice how the factorial limit is perfectly calculated at compile time!
    print_fp("Max Safe Factorial", FixedPointInt::max_factorial_n()); 
    std::cout << "\n";

    // 4. Trigonometry
    std::cout << "--- 4. TRIGONOMETRY (TABLE LOOKUPS) ---\n";
    // We expect sin(30) to be 0.5, cos(60) to be 0.5, and tan(45) to be 1.0
    for (int i = 0; i <= 360; ++i) {
        std::string temp = "Sin(" + std::to_string(i) + "⁰) ";
        print_fp(temp, Trig::sin(i));
    
        temp = "Cos(" + std::to_string(i) + "⁰) ";
        print_fp(temp, Trig::cos(i));

        temp = "Tan(" + std::to_string(i) + "⁰) ";
        print_fp(temp, Trig::tan(i));
        std::cout << std::endl;
    }
    // print_fp("Sin(30 degrees)", Trig::sin(30));
    // print_fp("Cos(60 degrees)", Trig::cos(60));
    // print_fp("Tan(45 degrees)", Trig::tan(45));
// 
    // // Test symmetry and negative angles
    // print_fp("Sin(210 degrees)", Trig::sin(210));  // Should be -0.5
    // print_fp("Cos(-60 degrees)", Trig::cos(-60));  // Should be 0.5
// 
    // // Test the Raycaster Survival Traps!
    // print_fp("Tan(90) [INFINITY]", Trig::tan(90)); // Should return the Max Positive Value!
    std::cout << "\n";

    // 5. Logical Operators
    std::cout << "--- 5. LOGICAL OPERATORS ---\n";
    FixedPointInt f(5, true);
    std::cout << "Is 5.0 == 5?      " << (f == 5 ? "TRUE" : "FALSE") << "\n";
    std::cout << "Is 5.0 > 4?       " << (f > 4 ? "TRUE" : "FALSE") << "\n";
    std::cout << "Is 5.0 <= 10.0?   " << (f <= FixedPointInt(10, true) ? "TRUE" : "FALSE") << "\n";

    std::cout << "\nAll tests completed. If these numbers look right, your math core is bulletproof.\n";
    
    return 0;
}