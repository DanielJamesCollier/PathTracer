// included at the bottom of Vec4.hpp
namespace djc_math {

//------------------------------------------------------------
template<typename T>
Vec4<T>::Vec4(T all) 
:   x(all)
,   y(all)
,   z(all)
,   w(all)
{
    // empty
}

//------------------------------------------------------------
template<typename T>
Vec4<T>::Vec4(T _x, T _y, T _z, T _w) 
:   x(_x)
,   y(_y)
,   z(_z)
,   w(_w)
{
    // empty
}

//------------------------------------------------------------
template<typename T>
Vec4<T>::Vec4(Vec2<T> const & vecXY, Vec2<T> const & vecZW)
:   x(vecXY.x)
,   y(vecXY.y)
,   z(vecZW.x)
,   w(vecZW.y)
{
    // empty
}

//------------------------------------------------------------
template<typename T>
Vec4<T>::Vec4(Vec2<T> const & vec, T _z, T _w)
:   x(vec.x)
,   y(vec.y)
,   z(_z)
,   w(_w)
{
    // empty
}

//------------------------------------------------------------
template<typename T>
Vec4<T>::Vec4(Vec3<T> const & vec, T _w) 
:   x(vec.x)
,   y(vec.y)
,   z(vec.z)
,   w(_w)
{
    // empty
}

// member - functions

//------------------------------------------------------------
template<typename T> T
Vec4<T>::length() const {
    return std::sqrt(x * x + y * y + z * z + w * w);
}

//------------------------------------------------------------
template<typename T> T
Vec4<T>::length2() const {
    return x * x + y * y + z * z + w * w;
}

//------------------------------------------------------------
template<typename T> void
Vec4<T>::normalise() {
    T length = std::sqrt(x * x + y * y + z * z + w * w);
    x /= length;
    y /= length;
    z /= length;
    w /= length;
}

//------------------------------------------------------------
template<typename T> T
Vec4<T>::dot(Vec4<T> const & vec) const {
     return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
}

//------------------------------------------------------------
template<typename T> Vec2<T>
Vec4<T>::toVec2() const {
    return Vec2<T>(x, y);
}

//------------------------------------------------------------
template<typename T> Vec3<T>
Vec4<T>::toVec3() const {
    return Vec3<T>(x, y, z);
}

// member - operator overloads

//------------------------------------------------------------
template<typename T> Vec4<T>
Vec4<T>::operator + () const {
    return Vec4<T>(x, y, z, w);
}

//------------------------------------------------------------
template<typename T> Vec4<T>
Vec4<T>::operator - () const {
    return Vec4<T>(-x, -y, -z, -w);
}

//------------------------------------------------------------
template<typename T> Vec4<T> &
Vec4<T>::operator += (Vec4<T> const & rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec4<T> &
Vec4<T>::operator -= (Vec4<T> const & rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec4<T> &
Vec4<T>::operator *= (Vec4<T> const & rhs) {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    w *= rhs.w;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec4<T> &
Vec4<T>::operator /= (Vec4<T> const & rhs) {
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;
    w /= rhs.w;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec4<T> &
Vec4<T>::operator += (T rhs) {
    x += rhs;
    y += rhs;
    z += rhs;
    w += rhs;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec4<T> &
Vec4<T>::operator -= (T rhs) {
    x -= rhs;
    y -= rhs;
    z -= rhs;
    w -= rhs;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec4<T> &
Vec4<T>::operator *= (T rhs) {
    x *= rhs;
    y *= rhs;
    z *= rhs;
    w *= rhs;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec4<T> &
Vec4<T>::operator /= (T rhs) {
    x /= rhs;
    y /= rhs;
    z /= rhs;
    w /= rhs;
    return *this;
}

// free function operator overloads

//------------------------------------------------------------
template<typename T> Vec4<T> 
operator + (Vec4<T> const & lhs, Vec4<T> const & rhs) {
    return Vec4<T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
}

//------------------------------------------------------------
template<typename T> Vec4<T> 
operator - (Vec4<T> const & lhs, Vec4<T> const & rhs) {
    return Vec4<T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
}

//------------------------------------------------------------
template<typename T> Vec4<T> 
operator * (Vec4<T> const & lhs, Vec4<T> const & rhs) {
    return Vec4<T>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w);
}

//------------------------------------------------------------
template<typename T> Vec4<T> 
operator / (Vec4<T> const & lhs, Vec4<T> const & rhs) {
    return Vec4<T>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w);
}

//------------------------------------------------------------
template<typename T> Vec4<T>
operator + (T lhs, Vec4<T> const & rhs) {
    return Vec4<T>(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z, lhs + rhs.z);
}

//------------------------------------------------------------
template<typename T> Vec4<T>
operator - (T lhs, Vec4<T> const & rhs) {
    return Vec4<T>(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z, lhs - rhs.z);
}

//------------------------------------------------------------
template<typename T> Vec4<T>
operator * (T lhs, Vec4<T> const & rhs) {
    return Vec4<T>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.z);
}

//------------------------------------------------------------
template<typename T> Vec4<T>
operator / (T lhs, Vec4<T> const & rhs) {
    return Vec4<T>(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z, lhs / rhs.z);
}

//------------------------------------------------------------
template<typename T> std::ostream &
operator << (std::ostream & lhs, Vec4<T> const & rhs) {
    lhs << "Vec4(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ", " << rhs.w << ")";
    return lhs;
}

// free functions

//------------------------------------------------------------
template<typename T> Vec4<T>
normalise(Vec4<T> const & vec) {
    T length = std::sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z) + (vec.w * vec.w));
    return Vec4<T>(vec.x / length, vec.y / length, vec.z / length, vec.w / length);
}

//------------------------------------------------------------
template<typename T> T
dot(Vec4<T> const & lhs, Vec4<T> const & rhs) {
    return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z) + (lhs.w * rhs.w);
}

} /* namespace djc_math */