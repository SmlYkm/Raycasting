#include "math/utils.hpp"
#include "math/Trig.hpp"

namespace engine {
    namespace math {
        const short unsigned int Trig::n_samples_m(91);
        unsigned short int Trig::precision_m(7);
        Fraction *Trig::sin_m(create_sin_m());

        Trig::Trig() {
        }

        Trig::~Trig() {
        }

        Fraction *Trig::create_sin_m() {
            static Fraction sin_arr[n_samples_m];

            for (int i = 0; i < n_samples_m; ++i) {
                sin_arr[i] = taylor_sin(i, precision_m);
            }

            return sin_arr;
        }

        Fraction Trig::taylor_sin(const int degrees, const int n) {
            Fraction result(degrees, 1);
            for (int i = 1; i < n; ++i) {
                int top = pow(degrees, 1 + 2*i);
                int bottom = factorial(1 + 2*i);
                if (i % 2 == 0) {
                    result += Fraction(top, bottom);
                } else {
                    result -= Fraction(top, bottom);
                }
                result.prevent_overflow();
            }
            return result;
        }

        Fraction Trig::sin(const int degrees) {
            return Fraction(degrees, 1);    // TODO
        }

        Fraction Trig::cos(const int degrees) {
            return Fraction(degrees, 1);    // TODO
        }

        Fraction Trig::tan(const int degrees) {
            return Fraction(degrees, 1);    // TODO
        }

    }
}