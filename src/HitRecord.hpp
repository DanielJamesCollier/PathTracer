#ifndef HitRecord_hpp
#define HitRecord_hpp

#include "djc_math/Vec3.hpp"

struct HitRecord {
    float time;
    djc_math::Vec3f point;
    djc_math::Vec3f normal;
    class Material * ptr_mat = nullptr;
};

#endif /* HitRecord_hpp */