#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include"hittable.h"

#include<memory>
#include<vector>

using std::shared_ptr;
using std::make_shared;
using std::vector;

class hittable_list: public hittable {
private:
    vector<shared_ptr<hittable>> objects;

public:
    hittable_list() {}
    hittable_list(shared_ptr<hittable> object) { add(object); }

    void clear() { objects.clear(); }
    void add(shared_ptr<hittable> object) { objects.push_back(object); }

    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;
};

#endif  // HITTABLE_LIST_H
