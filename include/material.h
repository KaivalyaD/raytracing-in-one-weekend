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

class metal: public material {
private:
    color3 albedo;

public:
    metal(const color3& a) : albedo(a) {}

    virtual bool scatter(const ray& r_incident, const hit_record& rec, color3& attenuation, ray& r_scattered) const override{
        vec3 reflected = reflect(unit_vector(r_incident.direction()), rec.normal);
        r_scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return dot(r_scattered.direction(), rec.normal) > 0.0f;
    }
};

#endif  // MATERIAL_H
