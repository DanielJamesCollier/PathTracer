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
    Ray(Vec3 const & origin, Vec3 const & direction);
    
    Vec3 const & origin() const;
    Vec3 const & direction() const;
    Vec3         pointAtParam(float t) const;
    
private:
    Vec3 m_origin;
    Vec3 m_direction;
};


#endif /* Ray_hpp */
