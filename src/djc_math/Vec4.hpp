#ifndef Vec4_hpp
#define Vec4_hpp

// std
#include <cmath>
#include <iostream>
#include <type_traits>

// my
#include "Vec2.hpp"
#include "Vec3.hpp"

namespace djc_math {

template<typename T = float>
class Vec4 final {
    static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value, "T must be intergral or floating point");
public: // RAII
    explicit Vec4(T all = T());
    Vec4(T _x, T _y, T _z, T _w);
    Vec4(Vec2<T> const & vec, T _z, T _w);
    Vec4(Vec2<T> const & vecXY, Vec2<T> const & vecZW);
    Vec4(Vec3<T> const & vec, T _w);
    ~Vec4() = default;

public: // member - functions
    T length() const;
    T length2() const;
    void normalise();
    T dot(Vec4<T> const & vec) const;
    // for cross cast to Vec3
    Vec2<T> toVec2() const;
    Vec3<T> toVec3() const;

public: // member - operator overloads

    Vec4<T> operator + () const;
    Vec4<T> operator - () const;

    Vec4<T> & operator += (Vec4<T> const & rhs);
    Vec4<T> & operator -= (Vec4<T> const & rhs);
    Vec4<T> & operator *= (Vec4<T> const & rhs);
    Vec4<T> & operator /= (Vec4<T> const & rhs);

    Vec4<T> & operator += (T rhs);
    Vec4<T> & operator -= (T rhs);
    Vec4<T> & operator *= (T rhs);
    Vec4<T> & operator /= (T rhs);

    T operator [] (int index) {
        switch(index) {
            case 0: return x; break;
            case 1: return y; break;
            case 2: return z; break;
            case 3: return w; break;
            default: 
                std::cout << "vec4 index invalid\n";
                return T(); // FIX: need to remove this operator for a better solution
                break;
        }
    }

public: // free function operator overloads - defined in Vec4.inl
    // Vec4<T> operator + (Vec4<T> const & lhs, Vec4<T> const & rhs);
    // Vec4<T> operator - (Vec4<T> const & lhs, Vec4<T> const & rhs);
    // Vec4<T> operator * (Vec4<T> const & lhs, Vec4<T> const & rhs);
    // Vec4<T> operator / (Vec4<T> const & lhs, Vec4<T> const & rhs);

    // Vec4<T> operator + (T lhs, Vec4<T> const & rhs);
    // Vec4<T> operator - (T lhs, Vec4<T> const & rhs);
    // Vec4<T> operator * (T lhs, Vec4<T> const & rhs);
    // Vec4<T> operator / (T lhs, Vec4<T> const & rhs);

    // Vec4<T> operator + (Vec4<T> const & lhs, float rhs);
    // Vec4<T> operator - (Vec4<T> const & lhs, float rhs);
    // Vec4<T> operator * (Vec4<T> const & lhs, float rhs);
    // Vec4<T> operator / (Vec4<T> const & lhs, float rhs);
    // std::ostream & operator << (std::ostream & lhs, Vec4<T> const & rhs);  

public: // free function operator overload for use with other classes - defined in Vec34.inl
    // Vec4<T> operator * (Mat4<T> const & rhs & lhs, Vec4<T> const & rhs); - defined in Mat4.inl

public: // free functions
    // Vec4<T> normalise(Vec4<T> const & vec);
    // T dot(Vec4<T> const & lhs, Vec4<T> const & rhs);

public: // public data
    T x;
    T y;
    T z;
    T w;
};

// for ease of use in C++ 14 - in C++ 17 class templates can be deduced
using Vec4i = Vec4<int>;
using Vec4f = Vec4<float>;
using Vec4d = Vec4<double>;

} /* namespace djc_math */
#include "inline/Vec4.inl"
#endif /* Vec4_hpp */