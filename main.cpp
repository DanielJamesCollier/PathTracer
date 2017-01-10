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

int main(int argc, const char * argv[]) {
    int width {200};
    int height {100};
    std::string outputLocation{"/Users/danielcollier/Desktop/path tracer output.ppm"};
    
    std::ofstream file;
    file.open(outputLocation);
    
    file << "P3\n" << width << " " << height << "\n255\n";
    
    for(int j {height - 1}; j >= 0; j--) {
        for(int i{0}; i < width; i++) {
            float r {static_cast<float>(i) / static_cast<float>(width)};
            float g {static_cast<float>(j) / static_cast<float>(height)};
            float b {0.2f};
            
            Vec3 colour(r,g,b);
            
            int ir {static_cast<int>(255.99 * colour.x())};
            int ig {static_cast<int>(255.99 * colour.y())};
            int ib {static_cast<int>(255.99 * colour.z())};
            
            file << ir << " " << ig << " " << ib << "\n";
        }
    }
    
    file.close();
    
    return 0;
}
