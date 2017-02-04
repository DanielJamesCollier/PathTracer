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

class Dialectric : public Material {
public:
    Dialectric(float refractiveIndex) :
        m_refractiveIndex(refractiveIndex)
    {
        //empty
    }

    virtual bool scatter(Ray const & ray, HitRecord const & record, Maths::Vec3 & attenuation, Ray & scattered) const {
        Maths::Vec3 outwardNormal;
        Maths::Vec3 reflected = Utils::reflect(ray.direction(), record.normal);
        float ni_over_nt;
        attenuation = Maths::Vec3(1.0f, 1.0f, 1.0f);

        Maths::Vec3 refracted;

        if(Maths::dot(ray.direction(), record.normal) > 0) {
            outwardNormal = -record.normal;
            ni_over_nt = m_refractiveIndex;
        } else {
            outwardNormal = record.normal;
            ni_over_nt = 1.0f / m_refractiveIndex;
        }

        if(Utils::refract(ray.direction(), outwardNormal, ni_over_nt, refracted)) {
            scattered = Ray(record.point, refracted);
        } else {
            scattered = Ray(record.point, reflected);
            return false;
        }

        return true;
    }
private:
    float m_refractiveIndex;
};
#endif /* Material_hpp */