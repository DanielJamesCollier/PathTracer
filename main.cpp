//
//  main.cpp
//  PathTracer
//
//  Created by Daniel Collier on 10/01/2017.
//  Copyright © 2017 Daniel Collier. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "Vec3.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"

//---------------------------------------------------------
float raySphereIntersect(Sphere const & sphere, Ray const & ray) {
    Maths::Vec3 oc = ray.origin() - sphere.centre();
    
    float a = Maths::dot(ray.direction(), ray.direction());
    float b = 2.0f * Maths::dot(oc, ray.direction());
    float c = Maths::dot(oc, oc) - (sphere.radius() * sphere.radius());
    float discriminant = b * b - 4 * a * c;
   
    if(discriminant < 0) {
        return -1;
    } else {
        return (-b - sqrt(discriminant)) / (2.0f * a);
    }
}

//---------------------------------------------------------
Maths::Vec3 backgroundColour(Ray const & r) {
    Maths::Vec3 unitDircetion = r.direction();
    unitDircetion.normalise();
    
    float t = 0.5f * (unitDircetion.getY() + 1.0f);
    
    return (1.0f - t) * Maths::Vec3(1.0f, 1.0f, 1.0f) + t * Maths::Vec3(0.5f, 0.7f, 1.0f);
}

//---------------------------------------------------------
Maths::Vec3 sphereColour(Ray const & r, float t) {
    Maths::Vec3 N = r.pointAtParam(t) - Maths::Vec3(0.0f,0.0f,-1.0f);
    
    N.normalise();
    
    return 0.5f * Maths::Vec3(N.getX() + 1.0f, N.getY() + 1.0f, N.getZ() + 1.0f);
}

//---------------------------------------------------------
int main(int argc, const char * argv[]) {
    int width  {2000};
    int height {1000};
    std::string outputLocation{"/Users/danielcollier/Desktop/path tracer output.ppm"};
    
    std::ofstream file;
    file.open(outputLocation);
    file << "P3\n" << width << " " << height << "\n255\n";
    
    Maths::Vec3 bottomLeft(-2.0, -1.0, -1.0);
    Maths::Vec3 horizontal( 4.0,  0.0,  0.0);
    Maths::Vec3 vertical  ( 0.0,  2.0,  0.0);
    Maths::Vec3 origin    ( 0.0,  0.0,  0.0);
    
    Sphere sphere(Maths::Vec3(0,0,-1), 0.5);

    for(int j {height - 1}; j >= 0; j--) {
        for(int i{0}; i < width; i++) {
            float u = float(i) / float(width);
            float v = float(j) / float(height);
            
            Ray ray(origin, bottomLeft + u*horizontal + v*vertical);
            Maths::Vec3 col;
            
            float t;
            if((t = raySphereIntersect(sphere, ray)) > 0.0f) {
                col = sphereColour(ray, t);
            } else {
                col = backgroundColour(ray);
            }
            
            int ir {static_cast<int>(255.99 * col.getX())};
            int ig {static_cast<int>(255.99 * col.getY())};
            int ib {static_cast<int>(255.99 * col.getZ())};
            
            file << ir << " " << ig << " " << ib << "\n";
        }
    }
    
    file.close();
    
    return 0;
}
