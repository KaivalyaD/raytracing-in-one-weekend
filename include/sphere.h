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

#endif  // SPHERE_H
