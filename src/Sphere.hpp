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
#include "Hitable.hpp"

class Sphere : public Hitable {
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

    virtual bool hit(Ray const & ray, float minT, float maxT, HitRecord & record) {
        Maths::Vec3 oc = ray.origin() - m_centre;
        auto a = Maths::dot(ray.direction(), ray.direction());
        auto b = Maths::dot(oc, ray.direction());
        auto c = Maths::dot(oc, oc) - (m_radius * m_radius);
        auto discriminant = b * b - a * c;
        
        if(discriminant > 0) {
            auto temp = (-b - sqrt(discriminant)) / a;

            if(temp < maxT && temp > minT) {
                record.time   = temp;
                record.point  = ray.pointAtParam(record.time);
                record.normal = (record.point - m_centre) / m_radius;
                return true;
            }
            
            temp = (-b + sqrt(discriminant)) / a;
            
            if(temp < maxT && temp > minT) {
                record.time   = temp;
                record.point  = ray.pointAtParam(record.time);
                record.normal = (record.point - m_centre) / m_radius;
                return true;
            }
        }
        return false;
    }
    
private:
    Maths::Vec3 m_centre;
    float       m_radius;
};
#endif /* Sphere_hpp */
