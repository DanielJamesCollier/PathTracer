#ifndef Mat3_hpp
#define Mat3_hpp

// std
#include <array>
#include <iostream>
#include <cstddef> // std::size_t

// my 
#include "Vec3.hpp"

namespace djc_math {

// template forward declarations
template<typename T> class Mat3;
template<typename T> Mat3<T> operator * (Mat3<T> const & lhs, Mat3<T> const & rhs);
template<typename T> Vec3<T> operator * (Mat3<T> const & lhs, Vec3<T> const & rhs);
template<typename T> std::ostream & operator << (std::ostream & lhs, Mat3<T> const & rhs);

template<typename T = float>
class Mat3 final {
    static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value, "T must be intergral or floating point");
    static_assert(std::is_nothrow_move_constructible<T>::value, "T must be no throw move constructable");

public: // friends
    template<typename U> 
    friend class Mat4;

public: // RAII
    Mat3();
    explicit Mat3(std::array<T, 9> matrix);
    ~Mat3() = default;

public: // friend free functions
    // friend void clear();
    // friend void clear(T value);

public: // friend operators - defined in Mat3.inl
    friend Mat3<T> operator *<> (Mat3<T> const & lhs, Mat3<T> const & rhs); // Mat3 * Mat3
    friend Vec3<T> operator *<> (Mat3<T> const & lhs, Vec3<T> const & rhs); // Mat3 * Vec3
    friend std::ostream & operator <<<> (std::ostream & lhs, Mat3<T> const & rhs); // std::cout << Mat3 

private: // private operators
    float & operator [] (std::size_t index);
    float const & operator [] (std::size_t index) const;

private: // private data
    std::array<T, 9> m_matrix;
};

// for ease of use in C++ 14 - in C++ 17 class templates can be deduced
using Mat3i = Mat3<int>;
using Mat3f = Mat3<float>;
using Mat3d = Mat3<double>;

} /* namespace djc_math */
#include "inline/Mat3.inl"
#endif /* Mat3_hpp */