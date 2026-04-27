#pragma once

#include "FixedPointInt.hpp"

namespace engine {
    namespace math {
        // Static class used for fast trig calculation
        // Uses fixed point arithmetic
        class Trig {
        private:
            static const FixedPointInt     *sin_m;          // Arr size (Interval) = [0, 90] degrees
            static const short unsigned int n_samples;  // 91, from 0⁰ to 90⁰

        private:
            Trig();  // Prevents instances
        
        public:
            Trig(Trig const&)           = delete;
            void operator=(Trig const&) = delete;
            ~Trig();

        private:
            static const FixedPointInt *create_sin_m();

        public:
            // Finally, the methods we care about
            static const FixedPointInt taylor_sin(const int degrees);
            static const FixedPointInt taylor_sin(const FixedPointInt& degrees);

            static const FixedPointInt sin(const int degrees);
            static const FixedPointInt sin(const FixedPointInt& degrees);
            static const FixedPointInt cos(const int degrees);
            static const FixedPointInt cos(const FixedPointInt& degrees);
            static const FixedPointInt tan(const int degrees);
            static const FixedPointInt tan(const FixedPointInt& degrees);
        };
    }
}