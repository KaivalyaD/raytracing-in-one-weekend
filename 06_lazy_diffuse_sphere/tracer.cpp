#include"../include/rtweekend.h"

#include"../include/vec3_color_ext.h"
#include"../include/hittable_list.h"
#include"../include/sphere.h"
#include"../include/camera.h"

#include<iostream>

vec3 random_in_unit_sphere() {
    while(true) {
        auto p = vec3::random(-1.0f, 1.0f);
        if(p.length_squared() >= 1.0f) continue;
        return p;
    }
}

color3 ray_color(const ray& r, const hittable_list& world, int depth) {
    hit_record rec;

    // if ray bounce limit exceeded, return
    if(depth <= 0)
        return color3(0.0f, 0.0f, 0.0f);

    if(world.hit(r, 0.0f, infinity, rec)) {
        point3 target = rec.p + rec.normal + random_in_unit_sphere();
        ray reflected = ray(rec.p, target - rec.p);
        return 0.5f * ray_color(reflected, world, depth - 1);
    }
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
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    // world
    hittable_list world;
    world.add(make_shared<sphere>(point3(0.0f, -50.5f, -1.0f), 50.0f));
    world.add(make_shared<sphere>(point3(0.0f, 0.0f, -1.0f), 0.5f));

    // camera
    auto viewport_height = 2.0f;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0f;
    camera cam = camera(viewport_width, viewport_height, focal_length);

    // render
    cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for(int j = image_height-1; j >= 0; --j) {
        clog << "\rScanlines remaining: " << j << ' ' << flush;
        for(int i = 0; i < image_width; ++i) {
            color3 pixel_color(0.0f, 0.0f, 0.0f);
            for(int s = 0; s < samples_per_pixel; ++s) {
                auto u = float(i + random_float()) / (image_width - 1);
                auto v = float(j + random_float()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(cout, pixel_color, samples_per_pixel);
        }
    }
    clog << "\nDone.\n";
}
