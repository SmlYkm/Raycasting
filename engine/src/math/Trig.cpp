#include "math/utils.hpp"
#include "math/Trig.hpp"

namespace engine {
    namespace math {
        const short unsigned int Trig::n_samples(91);
        const FixedPointInt* Trig::sin_m(create_sin_m());

        Trig::Trig() {
        }

        Trig::~Trig() {
        }

        const FixedPointInt* Trig::create_sin_m() {
            static FixedPointInt sin_arr[91];

            for (int i = 0; i < 91; ++i) {
                sin_arr[i] = taylor_sin(i);
            }

            return sin_arr;
        }

        const FixedPointInt Trig::taylor_sin(const FixedPointInt& degrees) {
            FixedPointInt pi = FixedPointInt::pi();
            FixedPointInt temp = pi * degrees;
            FixedPointInt radians(temp / 180);
            FixedPointInt result(0, true);
            
            const int max_fact = FixedPointInt::max_factorial_n().to_int();
            
            for (int n = 0; (1 + 2 * n) <= max_fact; ++n) {
                FixedPointInt exp_val(1 + 2 * n, true); 
                FixedPointInt term = radians.pow(1 + 2 * n) / exp_val.factorial();

                if (n % 2 == 0) {
                    result += term;
                } else {
                    result -= term;
                }
            }

            return result;
        }

        const FixedPointInt Trig::taylor_sin(const int degrees) {
            return taylor_sin(FixedPointInt(degrees, true));
        }

        const FixedPointInt Trig::sin(const int degrees) {
            // 1. Normalize angle to [0, 359]
            int angle = degrees % 360;
            if (angle < 0) angle += 360;

            // 2. Exploit symmetry to get the value from the 0-90 array
            if (angle <= 90) {
                return sin_m[angle];
            } else if (angle <= 180) {
                return sin_m[180 - angle];
            } else if (angle <= 270) {
                // Return negative (0 - value) since we don't have a unary minus operator yet
                return FixedPointInt(0, true) - sin_m[angle - 180];
            } else {
                return FixedPointInt(0, true) - sin_m[360 - angle];
            }
        }

        const FixedPointInt Trig::sin(const FixedPointInt& degrees) {
            return sin(degrees.to_int());
        }

        const FixedPointInt Trig::cos(const int degrees) {
            return sin(degrees + 90);
        }

        const FixedPointInt Trig::cos(const FixedPointInt& degrees) {
            return cos(degrees.to_int());
        }

        const FixedPointInt Trig::tan(const int degrees) {
            FixedPointInt c = cos(degrees);
            if (c == 0) {
                return FixedPointInt::max(); 
            }
            return sin(degrees) / c;
        }

        const FixedPointInt Trig::tan(const FixedPointInt& degrees) {
            return tan(degrees.to_int());
        }
    }
}