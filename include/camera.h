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

    // adjustable vertical field-of-view
    camera(float vfov, float aspect_ratio) {
        auto theta = degrees_to_radians(vfov);
        auto h = tanf(theta / 2.0f);
        auto viewport_height = 2.0f * h;
        auto viewport_width = aspect_ratio * viewport_height;

        auto focal_length = 1.0f;

        origin = point3(0.0f, 0.0f, 0.0f);
        horizontal = vec3(viewport_width, 0.0f, 0.0f);
        vertical = vec3(0.0f, viewport_height, 0.0f);
        lower_left = origin - (horizontal / 2.0f) - (vertical / 2.0f) - vec3(0.0f, 0.0f, focal_length);
    }

    camera(point3 position, point3 center, vec3 up, float vfov, float aspect_ratio) {
        auto theta = degrees_to_radians(vfov);
        auto h = tanf(theta / 2.0f);
        auto viewport_height = 2.0f * h;
        auto viewport_width = aspect_ratio * viewport_height;

        auto w = unit_vector(position - center);
        auto u = unit_vector(cross(up, w));
        auto v = cross(u, w);

        origin = position;
        horizontal = viewport_width * u;
        vertical = viewport_height * v;
        lower_left = origin - horizontal / 2.0f - vertical / 2.0f - w;
    }

    ray get_ray(float s, float t) const {
        return ray(origin, lower_left + s * horizontal + t * vertical - origin);
    }
};

#endif  // CAMERA_H
