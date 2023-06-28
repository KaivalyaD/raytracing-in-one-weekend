#ifndef SPHERE_H
#define SPHERE_H

#include"hittable.h"
#include"vec3.h"

class sphere: public hittable {
private:
    point3 cen;
    shared_ptr<material> mat_ptr;
    float rad;
public:
    sphere() {}
    sphere(point3 center, float radius) : cen(center), rad(radius) {}
    sphere(point3 center, float radius, shared_ptr<material> mat) : cen(center), rad(radius), mat_ptr(mat) {}

    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;
};

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
    vec3 outward_normal = (rec.p - cen) / rad;  // using this form so that -ve rad can give spheres with inward normals
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}

#endif  // SPHERE_H
