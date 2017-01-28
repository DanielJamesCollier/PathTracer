#ifndef Hitable_h
#define Hitable_h

#include "Vec3.hpp"
#include "Ray.hpp"
#include <limits>

struct HitRecord {
    float time;
    Maths::Vec3 point;
    Maths::Vec3 normal;
};

class Hitable {
public:
    virtual bool hit(Ray const & ray, float minT, float maxT, HitRecord & record) = 0;
};

class HitList : public Hitable {
public:
    HitList(Hitable ** scene, int hitableCount) :
        m_scene(scene)
    ,   m_hitableCount(hitableCount)
    {
        //empty
    }

    virtual bool hit(Ray const & ray, float minT, float maxT, HitRecord & record) {
        HitRecord tempRecord;
        bool hitAnything      = false;
        double currentClosest = DBL_MAX;

        for(int i = 0; i < m_hitableCount; i++) {
            if(m_scene[i]->hit(ray, minT, maxT, tempRecord)) {
                hitAnything = true;
                currentClosest = tempRecord.time;
                record = tempRecord;
            }
        }
        return hitAnything;
    }

private:
    Hitable ** m_scene;
    int        m_hitableCount;
};

#endif // Hitable_h