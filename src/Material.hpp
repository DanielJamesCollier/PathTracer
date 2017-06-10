#ifndef Material_hpp
#define Material_hpp

#include "Ray.hpp"
#include "HitRecord.hpp"
#include "djc_math/Vec3.hpp"
#include "Utils.hpp"

class Material {
public:
    virtual bool scatter(Ray const & ray, HitRecord const & record, djc_math::Vec3f & attenuation, Ray & scattered) const {
       // std::cout << "Default Scatter" << std::endl;
        return false;
    }
};

class Lambertian final : public Material {
public:
    explicit Lambertian(djc_math::Vec3f const & albedo) :
        m_albedo(albedo)
    {
        //empty
    }

    virtual bool scatter(Ray const & ray, HitRecord const & record, djc_math::Vec3f & attenuation, Ray & scattered) const {
        djc_math::Vec3f target(record.point + record.normal + Utils::randomInUnitSphere());
        scattered = Ray(record.point, target - record.point);
        attenuation = m_albedo;
        return true;

    }

private:
    djc_math::Vec3f m_albedo;
};

class Metal final : public Material {
public:
    Metal(djc_math::Vec3f const & albedo, float fuzz) :
        m_albedo(albedo)
    ,   m_fuzz(fuzz > 1 ? 1 : fuzz)
    {
        // empty
    }

    virtual bool scatter(Ray const & ray, HitRecord const & record, djc_math::Vec3f & attenuation, Ray & scattered) const {
        djc_math::Vec3f reflected = Utils::reflect(djc_math::normalise(ray.direction()), record.normal);
        scattered = Ray(record.point, reflected + m_fuzz * Utils::randomInUnitSphere());
        attenuation = m_albedo;
        return (scattered.direction()).dot(record.normal) > 0;
    }

private:
        djc_math::Vec3f m_albedo;
        float m_fuzz;
};

class Dialectric : public Material {
public:
    Dialectric(float refractiveIndex) :
        m_refractiveIndex(refractiveIndex)
    {
        //empty
    }

    virtual bool scatter(Ray const & ray, HitRecord const & record, djc_math::Vec3f & attenuation, Ray & scattered) const {
        djc_math::Vec3f outwardNormal;
        djc_math::Vec3f reflected = Utils::reflect(ray.direction(), record.normal);
        float ni_over_nt;
        attenuation = djc_math::Vec3f(1.0f, 1.0f, 1.0f);

        djc_math::Vec3f refracted;

        if(djc_math::dot(ray.direction(), record.normal) > 0) {
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