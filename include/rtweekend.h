#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include<cmath>
#include<limits>
#include<memory>
#include<random>

// usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// constants
const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385f;

// utility functions
inline float degrees_to_radians(float degrees) {
    return degrees * pi / 180.0f;
}

inline float random_float() {
    // returns a random float in [0, 1)
    static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    static std::mt19937 gen;
    return dist(gen);
}

inline float random_float(float min, float max) {
    // returns a random float in [min, max)
    return min + (max - min) * random_float();
}

inline float clamp(float x, float min, float max) {
    // clamps x in range [min, max]
    if(x < min) return min;
    if(x > max) return max;
    return x;
}

// common headers
#include"ray.h"
#include"vec3.h"

#endif  // RTWEEKEND_H
