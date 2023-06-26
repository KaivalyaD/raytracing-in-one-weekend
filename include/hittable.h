#ifndef HITTABLE_H
#define HITTABLE_H

#include"vec3.h"
#include"ray.h"

class hit_record {
public:
    point3 p;
    vec3 normal;
    float t;
    bool front_face;

public:
    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        // normal is calculated so that it is always against the incident ray
        front_face = dot(r.direction(), outward_normal) < 0.0f;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
    public:
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif  // HITTABLE_H
