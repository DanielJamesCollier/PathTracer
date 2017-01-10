//
//  Ray.cpp
//  PathTracer
//
//  Created by Daniel Collier on 10/01/2017.
//  Copyright © 2017 Daniel Collier. All rights reserved.
//

#include "Ray.hpp"

Ray::Ray(Vec3 const & origin, Vec3 const & direction)
:
    m_origin(origin)
,   m_direction(direction) {
    
}

Vec3 const &
Ray::origin() const {
    return m_origin;
}

Vec3 const &
Ray::direction() const {
    return m_direction;
}

Vec3
Ray::pointAtParam(float t) const {
    return m_origin.addN(m_direction.multN(t));
}
