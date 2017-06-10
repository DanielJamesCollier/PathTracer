#ifndef Utils_hpp
#define Utils_hpp

#include <cstdlib>
#include <cmath>
#include "djc_math/Vec3.hpp"

namespace Utils {

    static const float PI = 3.14159265359;

    //---------------------------------------------------------
    //#include <cstdlib> // rand() - random float between 0 & 1
    float randF() {
        return (double)rand() / ((double)RAND_MAX + 1);
    }

    //---------------------------------------------------------
    //#include "Vec3.hpp"
    djc_math::Vec3f reflect(djc_math::Vec3f const & lhs, djc_math::Vec3f const & rhs) {
        return lhs - 2 * lhs.dot(rhs) * rhs;
    }

    //---------------------------------------------------------
    //#include "Vec3.hpp"
    djc_math::Vec3f randomInUnitSphere() {
        djc_math::Vec3f p;
        do {
            djc_math::Vec3f randVec(Utils::randF(), Utils::randF(), Utils::randF());
            p = 2.0f * randVec - djc_math::Vec3f(1,1,1);
        } while(p.length2() >= 1.0f);
        return p;
    }

    //---------------------------------------------------------
    //#include <cmath>
    float schlock(float cosine, float refractiveIndex) {
        float r0 = (1 - refractiveIndex) / (1 + refractiveIndex);
        r0 = r0 * r0;
        return r0 + (1 - r0) * std::pow((1- cosine), 5);
    }

    //---------------------------------------------------------
    bool refract(djc_math::Vec3f const & v, djc_math::Vec3f const & n, float niOverNt, djc_math::Vec3f & refracted) {
        djc_math::Vec3f uv = djc_math::normalise(v);
        float dt = uv.dot(n);
        float discriminant = 1.0f - niOverNt * niOverNt * (1 - dt * dt);

        if(discriminant > 0.0f) {
            refracted = niOverNt * (uv - n * dt) - n * sqrtf(discriminant);
            return true;
        } else {
            return false;
        }
    }

} // namespace Utils
#endif /* Utils_hpp */