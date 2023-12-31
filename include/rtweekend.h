#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include<cmath>
#include<limits>
#include<memory>

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
