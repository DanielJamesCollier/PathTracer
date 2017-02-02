#ifndef HitRecord_hpp
#define HitRecord_hpp

#include "Vec3.hpp"

struct HitRecord {
    float time;
    Maths::Vec3 point;
    Maths::Vec3 normal;
    class Material * ptr_mat = nullptr;
};

#endif /* HitRecord_hpp */