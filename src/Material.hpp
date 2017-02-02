#ifndef Material_hpp
#define Material_hpp

#include "Ray.hpp"
#include "HitRecord.hpp"
#include "Vec3.hpp"
#include "Utils.hpp"

class Material {
public:
    virtual bool scatter(Ray const & ray, HitRecord const & record, Maths::Vec3 & attenuation, Ray & scattered) const {
       // std::cout << "Default Scatter" << std::endl;
        return false;
    }
};

class Lambertian final : public Material {
public:
    explicit Lambertian(Maths::Vec3 const & albedo) :
        m_albedo(albedo)
    {
        //empty
    }

    virtual bool scatter(Ray const & ray, HitRecord const & record, Maths::Vec3 & attenuation, Ray & scattered) const {
        Maths::Vec3 target(record.point + record.normal + Utils::randomInUnitSphere());
        scattered = Ray(record.point, target - record.point);
        attenuation = m_albedo;
        return true;

    }

private:
    Maths::Vec3 m_albedo;
};

class Metal final : public Material {
public:
    Metal(Maths::Vec3 const & albedo, float fuzz) :
        m_albedo(albedo)
    ,   m_fuzz(fuzz > 1 ? 1 : fuzz)
    {
        // empty
    }

    virtual bool scatter(Ray const & ray, HitRecord const & record, Maths::Vec3 & attenuation, Ray & scattered) const {
        Maths::Vec3 reflected = Utils::reflect(Maths::normalise(ray.direction()), record.normal);
        scattered = Ray(record.point, reflected + m_fuzz * Utils::randomInUnitSphere());
        attenuation = m_albedo;
        return (Maths::dot(scattered.direction(), record.normal) > 0);
    }

private:
        Maths::Vec3 m_albedo;
        float m_fuzz;
};
#endif /* Material_hpp */