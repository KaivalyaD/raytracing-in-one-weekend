#ifndef CAMERA_H
#define CAMERA_H

#include"rtweekend.h"

class camera {
private:
    point3 origin;
    point3 lower_left;
    vec3 horizontal;
    vec3 vertical;

public:
    camera(float viewport_width, float viewport_height, float focal_length) {
        origin = point3(0.0f, 0.0f, 0.0f);
        horizontal = vec3(viewport_width, 0.0f, 0.0f);
        vertical = vec3(0.0f, viewport_height, 0.0f);
        lower_left = origin - (horizontal / 2.0f) - (vertical / 2.0f) - vec3(0.0f, 0.0f, focal_length);
    }

    ray get_ray(float u, float v) const {
        return ray(origin, lower_left + u * horizontal + v * vertical - origin);
    }
};

#endif  // CAMERA_H
