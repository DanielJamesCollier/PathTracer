namespace djc_math {

// RAII

//------------------------------------------------------------
template<typename T>
Vec2<T>::Vec2(T all) 
:   x(all)
,   y(all)
{
    // empty
}

//------------------------------------------------------------
template<typename T>
Vec2<T>::Vec2(T _x, T _y) 
:   x(_x)
,   y(_y)
{
    // empty
}

// member - functions

//------------------------------------------------------------
template<typename T> T
Vec2<T>::length() const {
    return std::sqrt(x * x + y * y);
}

//------------------------------------------------------------
template<typename T> T
Vec2<T>::length2() const {
    return x * x + y * y;
}

//------------------------------------------------------------
template<typename T> void
Vec2<T>::normalise() {
    T length = std::sqrt(x * x + y * y);
    x /= length;
    y /= length;
}

//------------------------------------------------------------
template<typename T> T
Vec2<T>::dot(Vec2<T> const & vec) {
    return x * vec.x + y * vec.y;
}

// member - operator overloads

//------------------------------------------------------------
template<typename T> Vec2<T> 
Vec2<T>::operator + () const {
    return Vec2<T>(x, y);
}

//------------------------------------------------------------
template<typename T> Vec2<T> 
Vec2<T>::operator - () const {
    return Vec2<T>(-x, -y);
}

//------------------------------------------------------------
template<typename T> Vec2<T> &
Vec2<T>::operator += (Vec2<T> const & rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec2<T> &
Vec2<T>::operator -= (Vec2<T> const & rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec2<T> &
Vec2<T>::operator *= (Vec2<T> const & rhs) {
    x *= rhs.x;
    y *= rhs.y;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec2<T> &
Vec2<T>::operator /= (Vec2<T> const & rhs) {
    x /= rhs.x;
    y /= rhs.y;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec2<T> &
Vec2<T>::operator += (T rhs) {
    x += rhs;
    y += rhs;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec2<T> &
Vec2<T>::operator -= (T rhs) {
    x -= rhs;
    y -= rhs;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec2<T> &
Vec2<T>::operator *= (T rhs) {
    x *= rhs;
    y *= rhs;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec2<T> &
Vec2<T>::operator /= (T rhs) {
    x /= rhs;
    y /= rhs;
    return *this;
}

// free function operator overloads

//------------------------------------------------------------
template<typename T> Vec2<T>
operator + (Vec2<T> const & lhs, Vec2<T> const & rhs) {
    return Vec2<T>(lhs.x + rhs.x, lhs.y + rhs.y);
}

//------------------------------------------------------------
template<typename T> Vec2<T>
operator - (Vec2<T> const & lhs, Vec2<T> const & rhs) {
    return Vec2<T>(lhs.x - rhs.x, lhs.y - rhs.y);
}

//------------------------------------------------------------
template<typename T> Vec2<T>
operator * (Vec2<T> const & lhs, Vec2<T> const & rhs) {
    return Vec2<T>(lhs.x * rhs.x, lhs.y * rhs.y);
}

//------------------------------------------------------------
template<typename T> Vec2<T>
operator / (Vec2<T> const & lhs, Vec2<T> const & rhs) {
    return Vec2<T>(lhs.x / rhs.x, lhs.y / rhs.y);
}

//------------------------------------------------------------
template<typename T> Vec2<T>
operator + (T lhs, Vec2<T> const & rhs) {
    return Vec2<T>(lhs + rhs.x, lhs + rhs.y);
}

//------------------------------------------------------------
template<typename T> Vec2<T>
operator - (T lhs, Vec2<T> const & rhs) {
    return Vec2<T>(lhs - rhs.x, lhs - rhs.y);
}

//------------------------------------------------------------
template<typename T> Vec2<T>
operator * (T lhs, Vec2<T> const & rhs) {
    return Vec2<T>(lhs * rhs.x, lhs * rhs.y);
}

//------------------------------------------------------------
template<typename T> Vec2<T>
operator + (Vec2<T> const & lhs, T rhs) {
    return Vec2<T>(lhs.x + rhs, lhs.y + rhs);
}

//------------------------------------------------------------
template<typename T> Vec2<T>
operator - (Vec2<T> const & lhs, T rhs) {
    return Vec2<T>(lhs.x - rhs, lhs.y - rhs);
}

//------------------------------------------------------------
template<typename T> Vec2<T>
operator * (Vec2<T> const & lhs, T rhs) {
    return Vec2<T>(lhs.x * rhs, lhs.y * rhs);
}

//------------------------------------------------------------
template<typename T> Vec2<T>
operator / (Vec2<T> const & lhs, T rhs) {
    return Vec2<T>(lhs.x / rhs, lhs.y / rhs);
}

//------------------------------------------------------------
template<typename T> std::ostream &
operator << (std::ostream & lhs, Vec2<T> const & rhs) {
    return lhs << "Vec2(" << rhs.x << ", " << rhs.y << ")";
}

// free functions

//------------------------------------------------------------
template<typename T> Vec2<T>
normalise(Vec2<T> const & vec) {
    T length = std::sqrt((vec.x * vec.x) + (vec.y * vec.y));
    return Vec2<T>(vec.x / length, vec.y / length);
}

//------------------------------------------------------------
template<typename T> T
dot(Vec2<T> const & lhs, Vec2<T> const & rhs) {
    return (lhs.x * rhs.x) + (lhs.y * rhs.y);
}

} /* namespace djc_math */