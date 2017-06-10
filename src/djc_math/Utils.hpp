#ifndef MathsUtils_hpp
#define MathsUtils_hpp

// my
#include "Vec4.hpp"
#include "Constants.hpp"

// std
#include <cstdlib> 

namespace djc_math {

template<typename T> inline constexpr T 
toRadians(T degrees);

inline float 
randFBetweenZeroOne();

inline unsigned char 
randUCBetween0N255();

inline float
normalise(float valToNormalise, float min, float max);

template <typename T>
inline T lerp(T v0, T v1, float t);

template<typename T>
inline T clamp(T v, T low, T hi);

template<typename T>
inline void perspectiveDivide(Vec4<T> & vec);

} /* namespace djc_math */
#include "inline/Utils.inl"
#endif /* MathsUtils_hpp */