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

#endif  // VEC3_COLOR_EXT_H
