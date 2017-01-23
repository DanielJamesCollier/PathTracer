//
//  Ray.hpp
//  PathTracer
//
//  Created by Daniel Collier on 10/01/2017.
//  Copyright © 2017 Daniel Collier. All rights reserved.
//

#ifndef Ray_hpp
#define Ray_hpp

#include <stdio.h>
#include "Vec3.hpp"

class Ray {
public:
    Ray(Maths::Vec3 const & origin, Maths::Vec3 const & direction) :
        m_origin(origin)
    ,   m_direction(direction)
    {
        //empty
    }
    
    Maths::Vec3 const & origin() const {
        return m_origin;
    }
    Maths::Vec3 const & direction() const {
        return m_direction;
    }
    
    Maths::Vec3   pointAtParam(float t) const {
        return m_origin * m_direction;
    }
    
private:
    Maths::Vec3 m_origin;
    Maths::Vec3 m_direction;
};


#endif /* Ray_hpp */
