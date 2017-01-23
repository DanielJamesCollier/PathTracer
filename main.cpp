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

Maths::Vec3 colour(Ray const & r) {
    const Maths::Vec3 unitDircetion = r.direction();
    
    float t = 0.5f * (unitDircetion.getY() + 1.0f);
    
    return (Maths::Vec3(1.0f, 1.0f, 1.0f) * (1.0f - t)) + (Maths::Vec3(0.5f, 0.7f, 1.0f) * t);
}

int main(int argc, const char * argv[]) {
    int width {2304};
    int height {1440};
    std::string outputLocation{"/Users/danielcollier/Desktop/path tracer output.ppm"};
    
    std::ofstream file;
    file.open(outputLocation);
    
    Maths::Vec3 bottomLeft(-2.0, -1.0, -1.0);
    Maths::Vec3 horizontal(4.0, 0.0, 0.0);
    Maths::Vec3 vertical(0.0, 2.0, 0.0);
    Maths::Vec3 origin(0.0,0.0, 0.0);
    
    file << "P3\n" << width << " " << height << "\n255\n";
    
    for(int j {height - 1}; j >= 0; j--) {
        for(int i{0}; i < width; i++) {
            float r {static_cast<float>(i) / static_cast<float>(width)};
            float g {static_cast<float>(j) / static_cast<float>(height)};
            float b {0.2f};
            
            float u = float(i) / float(width);
            float v = float(j) / float(height);
            Ray ray(origin, bottomLeft + horizontal + u + vertical + v);
            
            Maths::Vec3 colour = Maths::Vec3(r,g,b);
            
            int ir {static_cast<int>(255.99 * colour.getX())};
            int ig {static_cast<int>(255.99 * colour.getY())};
            int ib {static_cast<int>(255.99 * colour.getZ())};
            
            file << ir << " " << ig << " " << ib << "\n";
        }
    }
    
    file.close();
    
    return 0;
}
