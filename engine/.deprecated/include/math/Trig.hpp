#pragma once

#include "Fraction.hpp"

namespace engine {
    namespace math {
        // Static class used for fast trig calculation
        class Trig {
        private:
            static const short unsigned int n_samples_m;
            static Fraction *sin_m;  // Arr size (Interval) = [0, 90] degrees
            static short unsigned int precision_m;

        private:
            Trig();  // Prevents instances
        
        public:
            Trig(Trig const&)           = delete;
            void operator=(Trig const&) = delete;
            ~Trig();

        private:
            static Fraction *create_sin_m();

        public:
            // Finally, the methods we care about
            static Fraction taylor_sin(const int degrees, const int n = 6);

            static Fraction sin(const int degrees);
            static Fraction cos(const int degrees);
            static Fraction tan(const int degrees);
        };
    }
}