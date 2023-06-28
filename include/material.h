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
    float fuzz;

public:
    metal(const color3& a) : albedo(a), fuzz(0.0f) {}
    metal(const color3& a, float fuzz) : albedo(a), fuzz(fuzz < 1.0f ? fuzz : 1.0f) {}

    virtual bool scatter(const ray& r_incident, const hit_record& rec, color3& attenuation, ray& r_scattered) const override{
        auto random_in_unit_sphere = [] () {
            while(true) {
                auto p = vec3::random(-1.0f, 1.0f);
                if(p.length_squared() >= 1.0f) continue;
                return p;
            }
        };
        vec3 reflected = reflect(unit_vector(r_incident.direction()), rec.normal);
        if(fuzz > 0.0f)
            r_scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
        else
            r_scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return dot(r_scattered.direction(), rec.normal) > 0.0f;
    }
};

class dielectric: public material {
private:
    float ri;

public:
    dielectric(float absolute_refractive_index) : ri(absolute_refractive_index) {}

    virtual bool scatter(const ray& r_incident, const hit_record& rec, color3& attenuation, ray& r_scattered) const override{
        attenuation = color3(1.0f, 1.0f, 1.0f);
        float refraction_ratio = rec.front_face ? (1.0f / ri) : ri;

        vec3 unit_direction = unit_vector(r_incident.direction());
        float cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0f);
        float sin_theta = sqrt(1 - cos_theta * cos_theta);

        // determine if refraction is at all possible
        bool cannot_refract = refraction_ratio * sin_theta > 1.0f;
        vec3 direction;

        // always refract when possible
        if(cannot_refract)
            direction = reflect(unit_direction, rec.normal);
        else
            direction = refract(unit_direction, rec.normal, refraction_ratio);

        r_scattered = ray(rec.p, direction);
        return true;
    }
};

#endif  // MATERIAL_H
