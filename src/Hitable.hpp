#ifndef Hitable_h
#define Hitable_h

#include "Vec3.hpp"
#include "Ray.hpp"
#include "HitRecord.hpp"

class Hitable {
public:
    virtual bool hit(Ray const & ray, float minT, float maxT, HitRecord & record) {
        return false;
    }
};

#endif // Hitable_h