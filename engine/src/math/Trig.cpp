#include "math/utils.hpp"
#include "math/Trig.hpp"

// #include <iostream>

namespace engine {
    namespace math {
        const short unsigned int Trig::n_samples(91);
        const FixedPointInt32* Trig::sin_m(create_sin_m());

        Trig::Trig() {
        }

        Trig::~Trig() {
        }

        const FixedPointInt32* Trig::create_sin_m() {
            static FixedPointInt32 sin_arr[91];

            for (int i = 0; i < 91; ++i) {
                sin_arr[i] = taylor_sin(i);
            }

            return sin_arr;
        }

        const FixedPointInt32 Trig::taylor_sin(const FixedPointInt32& degrees) {
            FixedPointInt32 pi = FixedPointInt32::pi();
            FixedPointInt32 temp = pi * degrees;
            FixedPointInt32 radians(temp / 180);
            FixedPointInt32 result(0, true);
            
            const int max_fact = FixedPointInt32::max_factorial_n().get_int();
            
            for (int n = 0; (1 + 2 * n) <= max_fact; ++n) {
                FixedPointInt32 exp_val(1 + 2 * n, true); 
                FixedPointInt32 term = radians.pow(1 + 2 * n) / exp_val.factorial();

                if (n % 2 == 0) {
                    result += term;
                } else {
                    result -= term;
                }
            }

            return result;
        }

        const FixedPointInt32 Trig::taylor_sin(const int degrees) {
            return taylor_sin(FixedPointInt32(degrees, true));
        }

        const FixedPointInt32 Trig::sin(const int degrees) {
            int angle = degrees % 360; //[0, 359]
            while (angle < 0) { 
                angle += 360;
            }

            if (angle <= 90) {
                return sin_m[angle];
            } else if (angle <= 180) {
                return sin_m[180 - angle];
            } else if (angle <= 270) {
                return -sin_m[angle - 180];
            } 
            return -sin_m[360 - angle];
        }

        const FixedPointInt32 Trig::sin(const FixedPointInt32& degrees) {
            return sin(degrees.get_int());
        }

        const FixedPointInt32 Trig::cos(const int degrees) {
            return sin(degrees + 90);
        }

        const FixedPointInt32 Trig::cos(const FixedPointInt32& degrees) {
            return cos(degrees.get_int());
        }

        const FixedPointInt32 Trig::tan(const int degrees) {
            FixedPointInt32 c = cos(degrees);
            if (c == 0)
                return FixedPointInt32::max(); 
            return sin(degrees) / c;
        }

        const FixedPointInt32 Trig::tan(const FixedPointInt32& degrees) {
            return tan(degrees.get_int());
        }
    }
}