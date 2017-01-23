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
#include "Vec3.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"

// check Math::dot


bool raySphereIntersect(Sphere const & sphere, Ray const & ray) {
    Maths::Vec3 oc = ray.origin() - sphere.centre();
    
    float a = Maths::dot(ray.direction(), ray.direction());
    float b = 2.0f * Maths::dot(oc, ray.direction());
    float c = Maths::dot(oc, oc) - sphere.radius() * sphere.radius();
    float discriminant = b * b - 4 * a * c;
    return (discriminant > 0);
}

Maths::Vec3 colour(Ray const & r) {
    Maths::Vec3 unitDircetion = r.direction();
    unitDircetion.normalise();
    
    float t = 0.5f * (unitDircetion.getY() + 1.0f);
    
    return (1.0f - t) * Maths::Vec3(1.0f, 1.0f, 1.0f) + t * Maths::Vec3(0.5f, 0.7f, 1.0f);
}

int main(int argc, const char * argv[]) {
    int width {1000};
    int height {500};
    std::string outputLocation{"/Users/danielcollier/Desktop/path tracer output.ppm"};
    
    std::ofstream file;
    file.open(outputLocation);
    file << "P3\n" << width << " " << height << "\n255\n";
    
    Maths::Vec3 bottomLeft(-2.0, -1.0, -1.0);
    Maths::Vec3 horizontal(4.0, 0.0, 0.0);
    Maths::Vec3 vertical(0.0, 2.0, 0.0);
    Maths::Vec3 origin(0.0, 0.0, 0.0);
    
    Sphere sphere(Maths::Vec3(0,0,-1), Maths::Vec3(1.0f, 0.0f, 0.0f), .5f);
    

    for(int j {height - 1}; j >= 0; j--) {
        for(int i{0}; i < width; i++) {
            float u = float(i) / float(width);
            float v = float(j) / float(height);
            
            Ray ray(origin, bottomLeft + u*horizontal + v*vertical);
            Maths::Vec3 col;
            
            if(raySphereIntersect(sphere, ray)) {
                col = sphere.colour();
           //    std::cout << "sphere" << std::endl;
            } else {
                //std::cout << "background" << std::endl;
                col = colour(ray);
            }
            
            int ir {static_cast<int>(255.99 * col.getX())};
            int ig {static_cast<int>(255.99 * col.getY())};
            int ib {static_cast<int>(255.99 * col.getZ())};
            
            //std::cout << col << std::endl;
            
            file << ir << " " << ig << " " << ib << "\n";
        }
    }
    
    file.close();
    
    return 0;
}
