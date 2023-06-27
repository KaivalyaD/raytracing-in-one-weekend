#include"../include/sphere.h"

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    vec3 oc = r.origin() - cen;
    auto a = r.direction().length_squared();    // 1st term of the quadratic equation
    auto half_b = dot(r.direction(), oc);       // 0.5f * 2nd term of the quadratic equation
    auto c = oc.length_squared() - rad * rad;   // 3rd term of the quadratic equation
    
    auto discriminant = half_b * half_b - a * c;
    if(discriminant < 0.0f)
        return false;
    auto sqrtd = sqrt(discriminant);

    // find nearest root that lies in range [t_min, t_max]
    auto root = (-half_b - sqrtd) / a;
    if(root < t_min || root > t_max) {
        root = (-half_b + sqrtd) / a;
        if(root < t_min || root > t_max)
            return false;
    }

    rec.t = root;
    rec.p = r.at(root);
    vec3 outward_normal = (rec.p - cen) / rad;
    rec.set_face_normal(r, outward_normal);

    return true;
}