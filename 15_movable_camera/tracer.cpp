#include"../include/rtweekend.h"

#include"../include/vec3_color_ext.h"
#include"../include/hittable_list.h"
#include"../include/sphere.h"
#include"../include/camera.h"
#include"../include/material.h"

#include<iostream>

color3 ray_color(const ray& r, const hittable_list& world, int depth) {
    hit_record rec;

    // if ray bounce limit exceeded, return
    if(depth <= 0)
        return color3(0.0f, 0.0f, 0.0f);

    if(world.hit(r, 0.001f, infinity, rec)) {
        ray scattered;
        color3 attenuation;
        if(rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * ray_color(scattered, world, depth - 1);
        }
        return color3(0.0f, 0.0f, 0.0f);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5f * unit_direction.y() + 0.5f;
    return (1.0f - t) * color3(1.0f, 1.0f, 1.0f) + t * color3(0.5f, 0.7f, 1.0f);
}

int main(void) {
    using namespace std;
    
    // image
    // const auto aspect_ratio = 16.0f / 9.0f;
    const auto aspect_ratio = 16.0f / 9.0f;
    const int image_width = 1024;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    // world
    hittable_list world;

    auto material_ground = make_shared<lambertian>(color3(0.8f, 0.8f, 0.0f));
    auto material_center = make_shared<lambertian>(color3(0.1f, 0.2f, 0.5f));
    auto material_left   = make_shared<dielectric>(1.5f);
    auto material_right  = make_shared<metal>(color3(0.8f, 0.6f, 0.3f), 0.0f);

    world.add(make_shared<sphere>(point3(0.0f, -100.5f, -1.0f), 100.0f, material_ground));
    world.add(make_shared<sphere>(point3(0.0f, 0.0f, -1.0f), 0.5f, material_center));
    world.add(make_shared<sphere>(point3(-1.0f, 0.0f, -1.0f), 0.5f, material_left));
    world.add(make_shared<sphere>(point3(-1.0f, 0.0f, -1.0f), -0.45f, material_left));
    world.add(make_shared<sphere>(point3( 1.0f, 0.0f, -1.0f), 0.5f, material_right));

    // camera
    camera cam = camera(point3(-2.0f, 1.25f, 1.0f), point3(0.0f, 0.0f, -1.0f), vec3(0.0f, 1.0f, 0.0f), 20.0f, aspect_ratio);

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
