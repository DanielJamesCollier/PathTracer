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
#include "Material.hpp"

class Sphere : public Hitable {
public:
    Sphere(Maths::Vec3 centre, float radius, Material * material) :
        m_centre(centre)
    ,   m_radius(radius)
    ,   m_material(material) 
    {
        // empty
    }

    virtual ~Sphere() {
        // empty - virtual because Hitable is an abstract class
    }
    
    Maths::Vec3 const & centre() const {
        return m_centre;
    }
    
    float radius() const {
        return m_radius;
    }

    virtual bool hit(Ray const & ray, float minT, float maxT, HitRecord & record) final {
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
    Maths::Vec3 m_centre;
    float       m_radius;
    Material *  m_material;
};
#endif /* Sphere_hpp */
