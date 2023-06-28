#ifndef CAMERA_H
#define CAMERA_H

#include"rtweekend.h"

class camera {
private:
    point3 origin;
    point3 lower_left;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    float lens_radius;

public:
    camera(float viewport_width, float viewport_height, float focal_length)
    : u(vec3(0.0f, 0.0f, 0.0f)),
      v(vec3(0.0f, 0.0f, 0.0f)),
      w(vec3(0.0f, 0.0f, 0.0f)),
      lens_radius(0.0f) {
        origin = point3(0.0f, 0.0f, 0.0f);
        horizontal = vec3(viewport_width, 0.0f, 0.0f);
        vertical = vec3(0.0f, viewport_height, 0.0f);
        lower_left = origin - (horizontal / 2.0f) - (vertical / 2.0f) - vec3(0.0f, 0.0f, focal_length);
    }

    // adjustable vertical field-of-view
    camera(float vfov, float aspect_ratio)
    : u(vec3(0.0f, 0.0f, 0.0f)),
      v(vec3(0.0f, 0.0f, 0.0f)),
      w(vec3(0.0f, 0.0f, 0.0f)),
      lens_radius(0.0f) {
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

    camera(point3 position, point3 center, vec3 up, float vfov, float aspect_ratio)
    : lens_radius(0.0f) {
        auto theta = degrees_to_radians(vfov);
        auto h = tanf(theta / 2.0f);
        auto viewport_height = 2.0f * h;
        auto viewport_width = aspect_ratio * viewport_height;

        w = unit_vector(position - center);
        u = unit_vector(cross(up, w));
        v = cross(u, w);

        origin = position;
        horizontal = viewport_width * u;
        vertical = viewport_height * v;
        lower_left = origin - horizontal / 2.0f - vertical / 2.0f - w;
    }

    camera(point3 position, point3 center, vec3 up, float vfov, float aspect_ratio, float aperture, float focus_distance) {
        auto theta = degrees_to_radians(vfov);
        auto h = tanf(theta / 2.0f);
        auto viewport_height = 2.0f * h;
        auto viewport_width = aspect_ratio * viewport_height;

        w = unit_vector(position - center);
        u = unit_vector(cross(up, w));
        v = cross(u, w);

        origin = position;
        horizontal = focus_distance * viewport_width * u;
        vertical = focus_distance * viewport_height * v;
        lower_left = origin - horizontal / 2.0f - vertical / 2.0f - focus_distance * w;
    
        lens_radius = aperture / 2.0f;
    }

    ray get_ray(float s, float t) const {
        auto random_in_unit_disc = [] () {
            while(true) {
                auto p = vec3(random_float(-1.0f, 1.0f), random_float(-1.0f, 1.0f), 0.0f);
                if(p.length_squared() >= 1.0f) continue;
                return p;
            }
        };
        vec3 offset = vec3(0.0f, 0.0f, 0.0f);
        if(lens_radius > 0.0f) {
            vec3 rd = lens_radius * random_in_unit_disc();
            offset = u * rd.x() + v * rd.y();
        }
        return ray(origin + offset, lower_left + s * horizontal + t * vertical - origin - offset);
    }
};

#endif  // CAMERA_H
