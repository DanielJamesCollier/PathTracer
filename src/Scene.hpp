#ifndef Scene_hpp
#define Scene_hpp

// own
#include "Sphere.hpp"
#include "Hitable.hpp"
#include "HitRecord.hpp"
#include "Material.hpp"

// djc_math
#include "djc_math/Vec3.hpp"

// std
#include <vector>
#include <memory>
#include <limits>

class Scene final {
public:
    Scene() = default;

    void addSphere(djc_math::Vec3f const & location, float radius, Material * material) {
        m_scene.push_back(std::make_unique<Sphere>(location, radius, material));
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
    std::vector<std::unique_ptr<Hitable>> m_scene;
};
#endif /* Scene_hpp */