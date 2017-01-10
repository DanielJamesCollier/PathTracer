//
//  Vec3.h
//  PathTracer
//
//  Created by Daniel Collier on 10/01/2017.
//  Copyright © 2017 Daniel Collier. All rights reserved.
//

#ifndef Vec3_hpp
#define Vec3_hpp

class Vec3 {
public:
    
    Vec3(float x, float y, float z);
    
    // standard functions
    //-------------------------------//
    float x() const;
    float y() const;
    float z() const;
    
    float r() const;
    float g() const;
    float b() const;

    float length() const;
    float length2() const;
    float dot(Vec3 const & vec) const;
    
    // Implace modification
    //-------------------------------//
    void  normaliseI();
    void  cross(Vec3 const & vec);
    void  addI(Vec3 const & vec);
    void  addI(float scalar);
    void  divI(Vec3 const & vec);
    void  divI(float scalar);
    void  multI(Vec3 const & vec);
    void  multI(float scalar);
    void  minusI(Vec3 const & vec);
    void  minusI(float scalar);
    
    // return as new vec modification
    //-------------------------------//
    Vec3  normaliseN() const;
    Vec3  cross(Vec3 const & vec) const;
    Vec3  addN(Vec3 const & vec) const;
    Vec3  addN(float scalar) const;
    Vec3  divN(Vec3 const & vec) const;
    Vec3  divN(float scalar) const;
    Vec3  multN(Vec3 const & vec) const;
    Vec3  multN(float scalar) const;
    Vec3  minusN(Vec3 const & vec) const;
    Vec3  minusN(float scalar) const;
   
private:
    float _x, _y, _z;
};


#endif /* Vec3_hpp */
