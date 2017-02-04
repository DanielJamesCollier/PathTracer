//
//  Camera.hpp
//  PathTracer
//
//  Created by Daniel Collier on 24/01/2017.
//  Copyright © 2017 Daniel Collier. All rights reserved.
//

#ifndef Camera_h
#define Camera_h

#include "Vec3.hpp"
#include "Ray.hpp"
#include "Utils.hpp"
#include <cmath>

//------------------------------------------------------------
class Camera final {
public:
    Camera(Maths::Vec3 const & position, float fov, float aspect) :
        m_fov(fov)
    ,   m_aspect(aspect)
     {
        float theta = fov * Utils::PI / 180;
        float halfHeight = tan(theta / 2);
        float halfWidth = aspect * halfHeight;

        m_lowerLeftCorner = Maths::Vec3(-halfWidth, -halfHeight, -1.0f);
        m_right = Maths::Vec3(2 * halfWidth, 0.0f, 0.0f);
        m_up = Maths::Vec3(0.0f, 2 * halfHeight, 0.0f);
        m_position = position;
    }

    Ray getRay(float u, float v) {
        return Ray(m_position, m_lowerLeftCorner + u * m_right + v * m_up);
    }

private:
    Maths::Vec3 m_position;
    Maths::Vec3 m_lowerLeftCorner;
    Maths::Vec3 m_right;
    Maths::Vec3 m_up;
    float m_fov;
    float m_aspect;
};
#endif /* Camera_h */
