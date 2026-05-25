#include <iostream>

#include "math/FixedPointInt32.hpp"
#include "math/Trig.hpp"

int main() {
    engine::math::FixedPointInt32 a(-1652, 2);
    engine::math::FixedPointInt32 b(64);
    engine::math::FixedPointInt32 c(a + b);

    std::cout << b.sqrt() << std::endl;

    std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;

    for (int i = 270; i < 360; ++i) {
        std::cout << engine::math::Trig::sin(i) << std::endl;
    }

    return 0;
}