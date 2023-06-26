#include<iostream>
#include"../include/vec3.h"
#include"../include/vec3_color_ext.h"
#include"../include/ray.h"

bool hit_sphere(const point3& center, float radius, const ray& r) {
    /**
     * sphere ray-intersection equation:
     * at real roots of t, a ray intersects the sphere:
     *      (t*t)(b.b) + (t)(2b.(A-C)) + (A-C).(A-C) - (r*r) = 0
     * where:
     *      ray equation is P(x) = (A + xb)
     *      A is the ray origin
     *      b is the ray direction
     *      C is the sphere center
     *      r is the sphere radius
     */
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction()); // 1st term of the quadratic equation
    auto b = 2.0f * dot(r.direction(), oc);     // 2nd term of the quadratic equation
    auto c = dot(oc, oc) - radius * radius;     // 3rd term of the quadratic equation
    auto discriminant = b * b - 4 * a * c;
    return discriminant > 0.0f;
}

color3 ray_color(const ray& r) {
    if(hit_sphere(point3(0.0f, 0.0f, -1.0f), 0.5f, r))
        return color3(1.0f, 0.0f, 0.0f);
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5f * unit_direction.y() + 0.5f;
    return (1.0f - t) * color3(1.0f, 1.0f, 1.0f) + t * color3(0.5f, 0.7f, 1.0f);
}

int main(void) {
    using namespace std;
    
    // image
    const auto aspect_ratio = 16.0f / 9.0f;
    const int image_width = 1024;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // camera
    auto viewport_height = 2.0f;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0f;

    auto origin = point3(0.0f, 0.0f, 0.0f);
    auto horizontal = vec3(viewport_width, 0.0f, 0.0f);
    auto vertical = vec3(0.0f, viewport_height, 0.0f);
    auto lower_left = origin - horizontal / 2.0f - vertical / 2.0f - vec3(0.0f, 0.0f, focal_length);

    // render
    cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for(int j = image_height-1; j >= 0; --j) {
        clog << "\rScanlines remaining: " << j << ' ' << flush;
        for(int i = 0; i < image_width; ++i) {
            auto u = float(i) / (image_width - 1);
            auto v = float(j) / (image_height - 1);
            ray r(origin, lower_left + u * horizontal + v * vertical - origin);
            color3 pixel_color = ray_color(r);
            write_color(cout, pixel_color);
        }
    }
    clog << "\nDone.\n";
}
