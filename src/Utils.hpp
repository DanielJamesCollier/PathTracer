#ifndef Utils_hpp
#define Utils_hpp

#include <cstdlib>
#include "Vec3.hpp"

namespace Utils {

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
    Maths::Vec3 randomInUnitSphere() {
        Maths::Vec3 p;
        do {
            Maths::Vec3 randVec(Utils::randF(), Utils::randF(), Utils::randF());
            p = 2.0 * randVec - Maths::Vec3(1,1,1);
        } while(Maths::length2(p) >= 1.0f);
        return p;
    }

} // namespace Utils
#endif /* Utils_hpp */