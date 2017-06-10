#ifndef Transform_hpp
#define Transform_hpp

// std
#include <array>
#include <cmath>

// my
#include "Vec3.hpp"
#include "Mat3.hpp"
#include "Mat4.hpp"

namespace djc_math {

//-----------------//
/*      Mat3       */
//-----------------//

// create new //

template<typename T> inline Mat3<T>
createMat3IdentityMatrix();

template<typename T> inline Mat3<T>
createMat3RotationMatrix(Vec3<T> const & vec);

//-------------------//
/*      Mat4        */
//-------------------//

// create new //

template<typename T> inline Mat4<T> 
createMat4IdentityMatrix();

template<typename T> inline Mat4<T>
createMat4TranslationMatrix(Vec3<T> const & vec);

template<typename T> inline Mat4<T>
createMat4RotationMatrix(Vec3<T> const & vec);

template<typename T> inline Mat4<T>
createMat4ScaleMatrix(Vec3<T> const & vec);

template<typename T> inline Mat4<T>
createMat4ModelMatrix(Vec3<T> const & position, Vec3<T> const & rotation, Vec3<T> const & scale);

template<typename T, typename U> inline Mat4<U>
createMat4OrthographicMatrix(T width, T height, U zNear, U zFar);

template<typename T> inline Mat4<T>
createMat4ProjectionMatrix(T fov, T aspect, T zNear, T zFar);

template<typename T> inline Mat4<T>
createMat4ViewMatrix(Vec3<T> const & eye, Vec3<T> const & centre, Vec3<T> const & up);

template<typename T> inline Mat4<T>
createMat4BirdsEyeViewMatrix();

template<typename T> inline Mat4<T>
createMat4ScreenSpaceTransform(T halfWifth, T halfHeight);

// use existing
template<typename T> inline void 
setMat4Identity(Mat4<T> & matrix);

//-------------------//
/*      Other        */
//-------------------//

template<typename T> inline void
transform(Vec4<T> & vec, Mat4<T> const & transformation);

template<typename T> inline Mat3<T>
rotate(T angle, Vec3<T> const & axis);

template<typename T> inline Mat4<T>
rotate(T angle, Vec4<T> const & axis);

} /* namespace djc_math */
#include "inline/Transform.inl"
#endif /* Transform_hpp */

