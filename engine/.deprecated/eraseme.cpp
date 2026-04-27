#include <iostream>
#include <cmath>

float estimate_sqrt_f(const float n, const float error, const short unsigned int n_recursions) {
    // We assume the person using this function is responsible and
    // knows that n must be positive
    float val = n - 1.0f;
    if (val < 0.0f) {
        val = -val;
    }
    if (n <= error || val <= error) {  // If n == 0 or n == 1
        return n;
    }
    float guess = n / 2.f;
    for (short unsigned int i = 0; i < n_recursions; ++i) { 
        float temp = guess * guess - n;
        if (temp < 0.0f) {
            temp = -temp;
        }
        if (temp <= error){
            return guess;
        }
        guess = (n / guess + guess) / 2.0f;
    }
    return guess;
}

float double_polygon_n_sides_f(const float l) {
    return sqrtf(
        2.0f * (1.0f - (sqrtf(1.0f - l*l/4.0f)))
    );
}

float estimate_pi_f(const short unsigned int n_recursions = 16) {
    unsigned int n = 6;  // Hexagon
    float l = 1.0f;      // Haxagon side length = radius
    for (short unsigned int i = 0; i < n_recursions; ++i) {
        n *= 2;
        l = double_polygon_n_sides_f(l);
    }
    return (l * static_cast<float>(n)) / 2.0f;
}

int main() {
    std::cout << estimate_pi_f(8) << std::endl;
    for (float i = 0.0f; i < 10.0f; ++i) {
        std::cout << estimate_sqrt_f(i*i, 0.01f, 16) << std::endl;
    }
    return 0;
}