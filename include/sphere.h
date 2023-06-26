#ifndef SPHERE_H
#define SPHERE_H

#include"hittable.h"
#include"vec3.h"

class sphere: public hittable {
private:
    point3 cen;
    float rad;
public:
    sphere() {}
    sphere(point3 center, float radius) : cen(center), rad(radius) {}

    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;
};

#endif  // SPHERE_H
