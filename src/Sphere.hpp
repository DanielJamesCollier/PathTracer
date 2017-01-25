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
#include "Ray.hpp"

class Sphere {
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
    
    // returns true if hit
    bool trace(Ray const & ray, Maths::Vec3 & colour) {
        Maths::Vec3 oc = ray.origin() - m_centre;
        
        float a = Maths::dot(ray.direction(), ray.direction());
        float b = 2.0f * Maths::dot(oc, ray.direction());
        float c = Maths::dot(oc, oc) - (m_radius * m_radius);
        float discriminant = b * b - 4 * a * c;
    
        if(discriminant < 0) {
            return false;
        }

        float t = (-b - sqrt(discriminant)) / (2.0f * a);

        if(t > 0.0f) {
            Maths::Vec3 N = Maths::normalise(ray.pointAtParam(t) - Maths::Vec3(0.0f,0.0f,-1.0f));
            colour =  0.5f * Maths::Vec3(N.getX() + 1.0f, N.getY() + 1.0f, N.getZ() + 1.0f);
            return true;
        }

        return false;
    }
    
private:
    Maths::Vec3 m_centre;
    float       m_radius;
};
#endif /* Sphere_hpp */
