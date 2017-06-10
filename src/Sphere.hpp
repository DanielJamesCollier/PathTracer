//
//  Sphere.h
//  PathTracer
//
//  Created by Daniel Collier on 23/01/2017.
//  Copyright © 2017 Daniel Collier. All rights reserved.
//

#ifndef Sphere_hpp
#define Sphere_hpp

#include "djc_math/Vec3.hpp"
#include "Ray.hpp"
#include "Hitable.hpp"
#include "Material.hpp"

class Sphere : public Hitable {
public:
    Sphere(djc_math::Vec3f centre, float radius, Material * material) :
        m_centre(centre)
    ,   m_radius(radius)
    ,   m_material(material) 
    {
        // empty
    }

    virtual ~Sphere() {
        // empty - virtual because Hitable is an abstract class
    }
    
    djc_math::Vec3f const & centre() const {
        return m_centre;
    }
    
    float radius() const {
        return m_radius;
    }

    virtual bool hit(Ray const & ray, float minT, float maxT, HitRecord & record) final {
        djc_math::Vec3f oc = ray.origin() - m_centre;
        auto a = djc_math::dot(ray.direction(), ray.direction());
        auto b = djc_math::dot(oc, ray.direction());
        auto c = djc_math::dot(oc, oc) - (m_radius * m_radius);
        auto discriminant = b * b - a * c;
        
        if(discriminant > 0) {
            auto temp = (-b - sqrt(discriminant)) / a;

            if(temp < maxT && temp > minT) {
                record.time   = temp;
                record.point  = ray.pointAtParam(record.time);
                record.normal = (record.point - m_centre) / m_radius;
                record.ptr_mat  = m_material;
                return true;
            }
            
            temp = (-b + sqrt(discriminant)) / a;
            
            if(temp < maxT && temp > minT) {
                record.time   = temp;
                record.point  = ray.pointAtParam(record.time);
                record.normal = (record.point - m_centre) / m_radius;
                record.ptr_mat  = m_material;
                return true;
            }
        }
        return false;
    }
    
private:
    djc_math::Vec3f m_centre;
    float       m_radius;
    Material *  m_material;
};
#endif /* Sphere_hpp */
