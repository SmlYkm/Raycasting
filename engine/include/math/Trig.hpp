#pragma once

#include "FixedPointInt32.hpp"

namespace engine {
    namespace math {
        // Static class used for fast trig calculation
        // Uses fixed point arithmetic
        class Trig {
        private:
            static const FixedPointInt32     *sin_m;          // Arr size (Interval) = [0, 90] degrees
            static const short unsigned int n_samples;  // 91, from 0⁰ to 90⁰

        private:
            Trig();  // Prevents instances
        
        public:
            Trig(Trig const&)           = delete;
            Trig(Trig const&&)          = delete;
            void operator=(Trig const&) = delete;
            void operator=(Trig const&&)= delete;
            ~Trig();

        private:
            static const FixedPointInt32 *create_sin_m();

        public:
            static const FixedPointInt32 taylor_sin(const int degrees);
            static const FixedPointInt32 taylor_sin(const FixedPointInt32 degrees);

            static const FixedPointInt32 sin(const int degrees);
            static const FixedPointInt32 sin(const FixedPointInt32 degrees);
            static const FixedPointInt32 cos(const int degrees);
            static const FixedPointInt32 cos(const FixedPointInt32 degrees);
            static const FixedPointInt32 tan(const int degrees);
            static const FixedPointInt32 tan(const FixedPointInt32 degrees);
        };
    }
}