#ifndef Utils_hpp
#define Utils_hpp

#include <cstdlib>
#include <cmath>
#include "Vec3.hpp"

namespace Utils {

    static const float PI = 3.14159265359;

    //---------------------------------------------------------
    //#include <cstdlib> // rand() - random float between 0 & 1
    float randF() {
        return (double)rand() / ((double)RAND_MAX + 1);
    }

    //---------------------------------------------------------
    //#include "Vec3.hpp"
    Maths::Vec3 reflect(Maths::Vec3 const & lhs, Maths::Vec3 const & rhs) {
        return lhs - 2 * Maths::dot(lhs, rhs) * rhs;
    }

    //---------------------------------------------------------
    //#include "Vec3.hpp"
    Maths::Vec3 randomInUnitSphere() {
        Maths::Vec3 p;
        do {
            Maths::Vec3 randVec(Utils::randF(), Utils::randF(), Utils::randF());
            p = 2.0 * randVec - Maths::Vec3(1,1,1);
        } while(Maths::length2(p) >= 1.0f);
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
    bool refract(Maths::Vec3 const & v, Maths::Vec3 const & n, float niOverNt, Maths::Vec3 & refracted) {
        Maths::Vec3 uv = Maths::normalise(v);
        float dt = Maths::dot(uv, n);
        float discriminant = 1.0f - niOverNt * niOverNt * (1 - dt * dt);

        if(discriminant > 0.0f) {
            refracted = niOverNt * (uv - n * dt) - n * sqrt(discriminant);
            return true;
        } else {
            return false;
        }
    }

} // namespace Utils
#endif /* Utils_hpp */