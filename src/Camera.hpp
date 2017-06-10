//
//  Camera.hpp
//  PathTracer
//
//  Created by Daniel Collier on 24/01/2017.
//  Copyright © 2017 Daniel Collier. All rights reserved.
//

#ifndef Camera_h
#define Camera_h

// own
#include "Ray.hpp"
#include "Utils.hpp"

// djc_math
#include "djc_math/Vec3.hpp"

// std
#include <cmath>

//------------------------------------------------------------
class Camera final {
public:
    Camera(djc_math::Vec3f const & position, float fov, float aspect) :
        m_fov(fov)
    ,   m_aspect(aspect)
     {
        float theta = fov * Utils::PI / 180;
        float halfHeight = tan(theta / 2);
        float halfWidth = aspect * halfHeight;

        m_lowerLeftCorner = djc_math::Vec3f(-halfWidth, -halfHeight, -1.0f);
        m_right = djc_math::Vec3f(2 * halfWidth, 0.0f, 0.0f);
        m_up = djc_math::Vec3f(0.0f, 2 * halfHeight, 0.0f);
        m_position = position;
    }

    Ray getRay(float u, float v) {
        return Ray(m_position, m_lowerLeftCorner + u * m_right + v * m_up);
    }

private:
    djc_math::Vec3f m_position;
    djc_math::Vec3f m_lowerLeftCorner;
    djc_math::Vec3f m_right;
    djc_math::Vec3f m_up;
    float m_fov;
    float m_aspect;
};
#endif /* Camera_h */
