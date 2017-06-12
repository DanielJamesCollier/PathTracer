namespace djc_math {

// RAII

//------------------------------------------------------------
template<typename T> 
Vec3<T>::Vec3(T all) 
:   x(all)
,   y(all)
,   z(all) 
{
    // empty
}

//------------------------------------------------------------
template<typename T>
Vec3<T>::Vec3(T _x, T _y, T _z) 
: x(_x)
, y(_y)
, z(_z)
{
    // empty
}

//------------------------------------------------------------
template<typename T>
Vec3<T>::Vec3(Vec2<T> const & vec, T _z) 
: x(vec.x)
, y(vec.y)
, z(_z)
{
    // empty
}

// member - functions

//------------------------------------------------------------
template<typename T> T
Vec3<T>::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

//------------------------------------------------------------
template<typename T> T
Vec3<T>::length2() const {
    return x * x + y * y + z * z;
}

//------------------------------------------------------------
template<typename T> void
Vec3<T>::normalise() {
    T length = std::sqrt(x * x + y * y + z * z);
    x /= length;
    y /= length;
    z /= length;
}

//------------------------------------------------------------
template<typename T> T
Vec3<T>::dot(Vec3<T> const & vec) const {
    return x * vec.x + y * vec.y + z * vec.z;
}

//------------------------------------------------------------
template<typename T> Vec3<T>
Vec3<T>::cross(Vec3<T> const & vec) const {
    return Vec3<T>((y * vec.z) - (z * vec.y),
                   (z * vec.x) - (x * vec.z),
                   (x * vec.y) - (y * vec.x));
}

//------------------------------------------------------------
template<typename T> Vec2<T>
Vec3<T>::toVec2() const {
    return Vec2<T>(x, y);
}

// member - operator overloads

//------------------------------------------------------------
template<typename T> Vec3<T>
Vec3<T>::operator + () const {
    return Vec3<T>(x, y, z);
}

//------------------------------------------------------------
template<typename T> Vec3<T>
Vec3<T>::operator - () const {
    return Vec3<T>(-x, -y, -z);
}

//------------------------------------------------------------
template<typename T> Vec3<T> &
Vec3<T>::operator += (Vec3<T> const & rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec3<T> &
Vec3<T>::operator -= (Vec3<T> const & rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec3<T> &
Vec3<T>::operator *= (Vec3<T> const & rhs) {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec3<T> &
Vec3<T>::operator /= (Vec3<T> const & rhs) {
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec3<T> &
Vec3<T>::operator += (T rhs) {
    x += rhs;
    y += rhs;
    z += rhs;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec3<T> &
Vec3<T>::operator -= (T rhs) {
    x -= rhs;
    y -= rhs;
    z -= rhs;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec3<T> &
Vec3<T>::operator *= (T rhs) {
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec3<T> &
Vec3<T>::operator /= (T rhs) {
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
}

// free function operator overloads

//------------------------------------------------------------
template<typename T> Vec3<T>
operator + (Vec3<T> const & lhs, Vec3<T> const & rhs) {
    return Vec3<T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

//------------------------------------------------------------
template<typename T> Vec3<T>
operator - (Vec3<T> const & lhs, Vec3<T> const & rhs) {
    return Vec3<T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

//------------------------------------------------------------
template<typename T> Vec3<T>
operator * (Vec3<T> const & lhs, Vec3<T> const & rhs) {
    return Vec3<T>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

//------------------------------------------------------------
template<typename T> Vec3<T>
operator / (Vec3<T> const & lhs, Vec3<T> const & rhs) {
    return Vec3<T>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
}

//------------------------------------------------------------
template<typename T> Vec3<T>
operator + (T lhs, Vec3<T> const & rhs) {
    return Vec3<T>(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z);
}

//------------------------------------------------------------
template<typename T> Vec3<T>
operator - (T lhs, Vec3<T> const & rhs) {
    return Vec3<T>(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z);
}

//------------------------------------------------------------
template<typename T> Vec3<T>
operator * (T lhs, Vec3<T> const & rhs) {
    return Vec3<T>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}

//------------------------------------------------------------
template<typename T> Vec3<T>
operator / (T lhs, Vec3<T> const & rhs) {
    return Vec3<T>(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z);
}

//------------------------------------------------------------
template<typename T> Vec3<T>
operator + (Vec3<T> const & lhs, T rhs) {
    return Vec3<T>(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);
}

//------------------------------------------------------------
template<typename T> Vec3<T>
operator - (Vec3<T> const & lhs, T rhs) {
    return Vec3<T>(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs);
}

//------------------------------------------------------------
template<typename T> Vec3<T>
operator * (Vec3<T> const & lhs, T rhs) {
    return Vec3<T>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

//------------------------------------------------------------
template<typename T> Vec3<T>
operator / (Vec3<T> const & lhs, T rhs) {
    return Vec3<T>(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}

//------------------------------------------------------------
template<typename T> std::ostream &
operator << (std::ostream & lhs, Vec3<T> const & rhs) {
    lhs << "Vec3\n-----------------\n";
    lhs << "Vec3(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")\n";
    lhs << "-----------------\n";
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