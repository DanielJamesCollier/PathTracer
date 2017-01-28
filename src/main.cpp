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
#include <limits>
#include <cmath>
#include <chrono>
#include <vector>
#include <random>

#include "Vec3.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"
#include "Hitable.hpp"

// checked
//---------------------------------------------------------
Maths::Vec3 colour(Ray const r,  Hitable * world) {
    HitRecord record;

    if(world->hit(r, 0.0f, FLT_MAX, record)) {
        return 0.5f * Maths::Vec3(record.normal.getX() + 1, record.normal.getY() + 1, record.normal.getZ() + 1);
    } else {
        Maths::Vec3 unitDircetion = Maths::normalise(r.direction());
        float t = 0.5f * (unitDircetion.getY() + 1.0f);
        return (1.0f - t) * Maths::Vec3(1.0f, 1.0f, 1.0f) + t * Maths::Vec3(0.5f, 0.7f, 1.0f);
    }
}

//---------------------------------------------------------
int main(int argc, const char * argv[]) {
    int width  {200};
    int height {100};
    std::string outputLocation{"render.ppm"};

    std::ofstream file;
    file.open(outputLocation);

    if(!file.is_open()) {
        return -1;
    }
     file << "P3\n" << width << " " << height << "\n255\n";  

    Camera cam(Maths::Vec3(0, 0, 0));
    Maths::Vec3 col(0,0,0);

    Hitable * list[2];
    list[1] = new Sphere(Maths::Vec3(0, 0, -1), 0.5);
    list[0] = new Sphere(Maths::Vec3(0, -100.5, -1), 100);

    Hitable * world = new HitList(list, 2);

    std::string buffer;
    buffer.reserve(width * height);

    for(int j {height - 1}; j >= 0; j--) {
        for(int i{0}; i < width; i++) {
            float u = (float)(i) / (float)(width);
            float v = (float)(j) / (float)(height);
            Ray ray(cam.getRay(u, v));

            col = colour(ray, world);
        
            int ir {static_cast<int>(255.99 * col.getX())};
            int ig {static_cast<int>(255.99 * col.getY())};
            int ib {static_cast<int>(255.99 * col.getZ())};
            
            buffer += std::to_string(ir);
            buffer += " ";
            buffer += std::to_string(ig);
            buffer += " ";
            buffer += std::to_string(ib);
            buffer += "\n";
        }
    }
    
    file << buffer;
    file.close();

    return 0;
}
