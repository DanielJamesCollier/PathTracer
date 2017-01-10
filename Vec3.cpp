//
//  Vec3.cpp
//  PathTracer
//
//  Created by Daniel Collier on 10/01/2017.
//  Copyright © 2017 Daniel Collier. All rights reserved.
//

#include "Vec3.hpp"
#include <math.h>

Vec3::Vec3(float x, float y, float z)
:
    _x(x)
,   _y(y)
,   _z(z) {
    
}

// standard functions
//-------------------------------//
float
Vec3::x() const {
    return _x;
}

float
Vec3::y() const {
    return _y;
}

float
Vec3::z() const {
    return _z;
}

float
Vec3::r() const {
    return _x;
}

float
Vec3::g() const {
    return _y;
}

float
Vec3::b() const {
    return _z;
}


float
Vec3::length() const {
    return sqrtf((_x * _x) + (_y * _y) + (_z * _z));
}

float
Vec3::length2() const {
    return (_x * _x) + (_y * _y) + (_z * _z);
}

float
Vec3::dot(Vec3 const & vec) const {
    return (_x * vec._x) + (_y * vec._y) + (_z * vec._z);
}

// implace modification
//-------------------------------//
void
Vec3::normaliseI()  {
    float l = length();
    _x /= l;
    _y /= l;
    _z /= l;
}

void
Vec3::cross(const Vec3 &vec) {
    float x = (_y * vec._z) - (_z * vec._y);
    float y = (_z * vec._x) - (_x * vec._z);
    float z = (_x * vec._y) - (_y * vec._x);
    
    _x = x;
    _y = y;
    _z = z;
}

void
Vec3::addI(Vec3 const & vec) {
    _x += vec._x;
    _y += vec._y;
    _z += vec._z;
}

void
Vec3::addI(float scalar) {
    _x += scalar;
    _y += scalar;
    _z += scalar;
}

void
Vec3::divI(Vec3 const & vec) {
    _x /= vec._x;
    _y /= vec._y;
    _z /= vec._z;
}

void
Vec3::divI(float scalar) {
    _x /= scalar;
    _y /= scalar;
    _z /= scalar;
}

void
Vec3::multI(Vec3 const & vec) {
    _x *= vec._x;
    _y *= vec._y;
    _z *= vec._z;
}

void
Vec3::multI(float scalar) {
    _x *= scalar;
    _y *= scalar;
    _z *= scalar;
}

void
Vec3::minusI(Vec3 const & vec) {
    _x -= vec._x;
    _y -= vec._y;
    _z -= vec._z;
}

void
Vec3::minusI(float scalar) {
    _x -= scalar;
    _y -= scalar;
    _z -= scalar;
}

// return new vec modification
//-------------------------------//
Vec3
Vec3::normaliseN() const {
    float l = length();
    return Vec3(_x / l, _y / l, _z / l);
}

Vec3
Vec3::cross(const Vec3 &vec) const {
    float x = (_y * vec._z) - (_z * vec._y);
    float y = (_z * vec._x) - (_x * vec._z);
    float z = (_x * vec._y) - (_y * vec._x);
    
    return Vec3(x,y,z);
}

Vec3
Vec3::addN(Vec3 const & vec) const {
    return Vec3(_x + vec._x, _y + vec._y, _z + vec._z);
}

Vec3
Vec3::addN(float scalar) const {
    return Vec3(_x + scalar, _y + scalar, _z + scalar);
}

Vec3
Vec3::divN(Vec3 const & vec) const {
    return Vec3(_x / vec._x, _y / vec._y, _z / vec._z);
}

Vec3
Vec3::divN(float scalar) const {
    return Vec3(_x / scalar, _y / scalar, _z / scalar);
}

Vec3
Vec3::multN(Vec3 const & vec) const {
    return Vec3(_x * vec._x, _y * vec._y, _z * vec._z);
}

Vec3
Vec3::multN(float scalar) const {
    return Vec3(_x * scalar, _y * scalar, _z * scalar);
}

Vec3
Vec3::minusN(Vec3 const & vec) const {
    return Vec3(_x - vec._x, _y - vec._y, _z - vec._z);
}

Vec3
Vec3::minusN(float scalar) const {
    return Vec3(_x - scalar, _y - scalar, _z - scalar);
}
