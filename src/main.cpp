#include <iostream>

#include "math/FixedPointInt32.hpp"

int main() {
    engine::math::FixedPointInt32 a(-1652, 2);
    engine::math::FixedPointInt32 b(64);
    engine::math::FixedPointInt32 c(a + b);

    std::cout << b.sqrt() << std::endl;

    std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;

    return 0;
}