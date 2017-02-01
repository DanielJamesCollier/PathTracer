#ifndef Hitable_h
#define Hitable_h

#include "Vec3.hpp"
#include "Ray.hpp"

struct HitRecord {
    float time;
    Maths::Vec3 point;
    Maths::Vec3 normal;
};

class Hitable {
public:
    virtual bool hit(Ray const & ray, float minT, float maxT, HitRecord & record) {
        return false;
    }
};

#endif // Hitable_h