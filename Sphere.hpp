//
//  Sphere.h
//  PathTracer
//
//  Created by Daniel Collier on 23/01/2017.
//  Copyright © 2017 Daniel Collier. All rights reserved.
//

#ifndef Sphere_hpp
#define Sphere_hpp

#include "Vec3.hpp"

class Sphere final {
    
public:
    Sphere(Maths::Vec3 centre, float radius) :
        m_centre(centre)
    ,   m_radius(radius) {
        // empty
    }
    
    Maths::Vec3 const & centre() const {
        return m_centre;
    }
    
    float radius() const {
        return m_radius;
    }
    
private:
    Maths::Vec3 m_centre;
    float       m_radius;
};
#endif /* Sphere_hpp */
