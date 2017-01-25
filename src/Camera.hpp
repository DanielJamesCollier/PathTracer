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

class Camera {
public:
    Camera(Maths::Vec3 const & position) :
        m_position(position)
    ,   m_lowerLeftCorner(Maths::Vec3(-2.0f, -1.0f, -1.0f))
    ,   m_right(Maths::Vec3(4.0f, 0.0f, 0.0f))
    ,   m_up(Maths::Vec3(0.0f, 2.0f, 0.0f))
    {
        //empty
    }
    
    Ray getRay(float u, float v) {
        return Ray(m_position, m_lowerLeftCorner + u * m_right + v * m_up);
    }
    
    
private:
    Maths::Vec3 m_position;
    Maths::Vec3 m_lowerLeftCorner;
    Maths::Vec3 m_right;
    Maths::Vec3 m_up;
};


#endif /* Camera_h */
