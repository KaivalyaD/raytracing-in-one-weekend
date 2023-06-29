#include"../include/rtweekend.h"

#include"../include/vec3_color_ext.h"
#include"../include/hittable_list.h"
#include"../include/sphere.h"
#include"../include/camera.h"
#include"../include/material.h"

#include<iostream>

hittable_list final_scene() {
    hittable_list world;

    auto material_ground = make_shared<lambertian>(color3(0.5f, 0.5f, 0.5f));
    world.add(make_shared<sphere>(point3(0.0f, -1000.0f, 0.0f), 1000.0f, material_ground));

    for(int a = -11; a < 11; ++a) {
        for(int b = -11; b < 11; ++b) {
            auto choose_material = random_float();
            point3 center(a + 0.9f * random_float(), 0.2f, b + 0.9f * random_float());

            if((center - point3(4.0f, 0.2f, 0.0f)).length() <= 0.9f)
                continue;

            shared_ptr<material> sphere_material;
            if(choose_material < 0.8f) {
                // diffuse
                auto albedo = color3::random() * color3::random();
                sphere_material = make_shared<lambertian>(albedo);
                world.add(make_shared<sphere>(center, 0.2f, sphere_material));
            } else if(choose_material < 0.95f) {
                // metal
                auto albedo = color3::random(0.5f, 1.0f);
                auto fuzz = random_float(0.0f, 0.5f);
                sphere_material = make_shared<metal>(albedo, fuzz);
                world.add(make_shared<sphere>(center, 0.2f, sphere_material));
            } else {
                // dielectric
                sphere_material = make_shared<dielectric>(1.5f);
                world.add(make_shared<sphere>(center, 0.2f, sphere_material));
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5f);
    world.add(make_shared<sphere>(point3(0.0f, 1.0f, 0.0f), 1.0f, material1));

    auto material2 = make_shared<lambertian>(color3(0.4f, 0.2f, 0.1f));
    world.add(make_shared<sphere>(point3(-4.0f, 1.0f, 0.0f), 1.0f, material2));

    auto material3 = make_shared<metal>(color3(0.7f, 0.6f, 0.5f), 0.0f);
    world.add(make_shared<sphere>(point3(4.0f, 1.0f, 0.0f), 1.0f, material3));

    return world;
}

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
    const auto aspect_ratio = 3.0f / 2.0f;
    const int image_width = 1200;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 500;
    const int max_depth = 50;

    // world
    hittable_list world = final_scene();

    // camera
    point3 position(point3(13.0f, 1.25f, 3.0f));
    point3 center(point3(0.0f, 0.0f, 0.0f));
    vec3 up(point3(0.0f, 1.0f, 0.0f));
    auto aperture = 0.1f;
    auto dist_to_focus = 10.0f;
    camera cam = camera(position, center, up, 20.0f, aspect_ratio, aperture, dist_to_focus);

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
