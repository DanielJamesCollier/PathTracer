#ifndef Vec2_hpp
#define Vec2_hpp

// std
#include <cmath>
#include <iostream>
#include <type_traits>

namespace djc_math {

template<typename T = float>
class Vec2 final {
    static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value, "T must be intergral or floating point");
public: // RAII
    explicit Vec2(T all = T());
    Vec2(T _x, T _y);
    ~Vec2() = default;

public: // member - functions
     T length() const;
     T length2() const;
     void normalise();
     T dot(Vec2<T> const & vec);

public: // member - operator overloads
    Vec2<T>   operator + () const;
    Vec2<T>   operator - () const;
    
    Vec2<T> & operator += (Vec2<T> const & rhs);
    Vec2<T> & operator -= (Vec2<T> const & rhs);
    Vec2<T> & operator *= (Vec2<T> const & rhs);
    Vec2<T> & operator /= (Vec2<T> const & rhs);

    Vec2<T> & operator += (T rhs);
    Vec2<T> & operator -= (T rhs);
    Vec2<T> & operator *= (T rhs);
    Vec2<T> & operator /= (T rhs);


public: // free function operator overloads - defined in Vec2.inl
    // Vec2<T> operator + (Vec2<T> const & lhs, Vec2<T> const & rhs);
    // Vec2<T> operator - (Vec2<T> const & lhs, Vec2<T> const & rhs);
    // Vec2<T> operator * (Vec2<T> const & lhs, Vec2<T> const & rhs);
    // Vec2<T> operator / (Vec2<T> const & lhs, Vec2<T> const & rhs);

    // Vec2<T> operator + (T lhs, Vec2<T> const & rhs);
    // Vec2<T> operator - (T lhs, Vec2<T> const & rhs);
    // Vec2<T> operator * (T lhs, Vec2<T> const & rhs);
    // Vec2<T> operator / (T lhs, Vec2<T> const & rhs);

    // Vec2<T> operator + (Vec2<T> const & lhs, float rhs);
    // Vec2<T> operator - (Vec2<T> const & lhs, float rhs);
    // Vec2<T> operator * (Vec2<T> const & lhs, float rhs);
    // Vec2<T> operator / (Vec2<T> const & lhs, float rhs);

    // std::ostream & operator << (std::ostream & lhs, Vec2<T> const & rhs);  

public: // free function operator overload for use with other classes
    // Vec2<T> operator * (Mat2<T> const & rhs & lhs, Vec2<T> const & rhs); - defined in Mat2.inl

public: // free functions
    // Vec2<T> normalise(Vec2<T> const & vec);
    // T dot(Vec2<T> const & lhs, Vec2<T> const & rhs);

public:
    T x;
    T y;
};

// for ease of use in C++ 14 - in C++ 17 class templates can be deduced
using Vec2i = Vec2<int>;
using Vec2f = Vec2<float>;
using Vec2d = Vec2<double>;

} /* namespace djc_math */
#include "inline/Vec2.inl"
#endif /* Vec2_hpp */