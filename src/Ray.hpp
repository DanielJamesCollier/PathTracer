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
#include "djc_math/Vec3.hpp"

class Ray final {
public:
    Ray() {
        // empty
    }
    
    Ray(djc_math::Vec3f const & origin, djc_math::Vec3f const & direction) :
        m_origin(origin)
    ,   m_direction(direction) {
        //empty
    }
    
    djc_math::Vec3f const & origin() const {
        return m_origin;
    }
    djc_math::Vec3f const & direction() const {
        return m_direction;
    }
    
    djc_math::Vec3f pointAtParam(float t) const {
        return m_origin + t * m_direction;
    }

private:
    djc_math::Vec3f m_origin;
    djc_math::Vec3f m_direction;
};
#endif /* Ray_hpp */
