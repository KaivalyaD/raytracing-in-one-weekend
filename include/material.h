#ifndef MATERIAL_H
#define MATERIAL_H

#include"rtweekend.h"
#include"hittable.h"

struct hit_record;

class material {
public:
    virtual bool scatter(const ray& r_incident, const hit_record& rec, color3& attenuation, ray& r_scattered) const = 0;
};

class lambertian: public material {
private:
    color3 albedo;

public:
    lambertian(const color3& a) : albedo(a) {}

    virtual bool scatter(const ray& r_incident, const hit_record& rec, color3& attenuation, ray& r_scattered) const override {
        auto random_unit_vector = [] () {
            vec3 p;
            while(true) {
                p = vec3::random(-1.0f, 1.0f);
                if(p.length_squared() >= 1.0f) continue;
                return unit_vector(p);
            }
        };
        auto scatter_direction = rec.normal + random_unit_vector();
        
        // to prevent further NaNs and infinities
        if(scatter_direction.near_zero())
            scatter_direction = rec.normal;

        r_scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }
};

#endif  // MATERIAL_H
