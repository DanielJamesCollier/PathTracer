#ifndef Scene_hpp
#define Scene_hpp

#include <vector>
#include <memory>
#include <limits>

#include "Sphere.hpp"
#include "Hitable.hpp"

class Scene {
public:
    Scene() = default;

    void addSphere(Maths::Vec3 const & location, float radius) {
        m_scene.push_back(std::make_unique<Sphere>(location, radius));
    }

    bool hit(Ray const & ray, float minT, float maxT, HitRecord & record) const {
        HitRecord tempRecord;
        auto hitAnything = false;
        auto currentClosest = std::numeric_limits<double>::max();;

        for(auto && i : m_scene) {
            if(i->hit(ray, minT, maxT, tempRecord)) {
                hitAnything = true;
                currentClosest = tempRecord.time;
                record = tempRecord;
            }
        }
        return hitAnything;
    }

private:
    std::vector<std::unique_ptr<Hitable> > m_scene;
};
#endif /* Scene_hpp */