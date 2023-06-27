#ifndef VEC3_COLOR_EXT_H
#define VEC3_COLOR_EXT_H

#include"vec3.h"
#include <iostream>

// write translated (0.0f, 1.0f) --> (0, 255) values of each color component
void write_color(std::ostream& out, color3 pixel_color) {
    out << static_cast<int>(255.999 * pixel_color.r()) << ' '
        << static_cast<int>(255.999 * pixel_color.g()) << ' '
        << static_cast<int>(255.999 * pixel_color.b()) << '\n';
}

// write translated (0.0f, 1.0f) --> (0, 255) values of each color component
void write_color(std::ostream& out, color3 pixel_color, int samples_per_pixel) {
    auto r = pixel_color.r();
    auto g = pixel_color.g();
    auto b = pixel_color.b();

    // divide color by number of samples
    auto scale = 1.0f / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;
    
    // write translated (0.0f, 1.0f) --> (0, 255) values of each color component
    out << static_cast<int>(256 * clamp(r, 0.0f, 0.999f)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0f, 0.999f)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0f, 0.999f)) << '\n';
}

#endif  // VEC3_COLOR_EXT_H
