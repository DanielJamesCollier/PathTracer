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

//---------------------------------------------------------
float randF(float start, float end) {
    static std::random_device rand_dev;
    static std::mt19937 generator(rand_dev());
    static std::uniform_real<float> distr(start, end);
    return distr(generator);
}

//---------------------------------------------------------
Maths::Vec3 randomInUnitSphere() {
    Maths::Vec3 p;
    do {
        float x = randF(0.0f, 1.0f);
        float y = randF(0.0f, 1.0f);
        float z = randF(0.0f, 1.0f);
        Maths::Vec3 randVec(x,y,z);
        //std::cout << randVec << std::endl;
        p = 2.0 * randVec - Maths::Vec3(1,1,1);
    } while(Maths::length2(p) >= 1.0f);
    return p;
}

//not working
//---------------------------------------------------------
Maths::Vec3 colourDiffuse(Ray const r,  Hitable * world) {
    HitRecord record;

    if(world->hit(r, 0.001f, FLT_MAX, record)) {
        Maths::Vec3 target = record.point + record.normal + randomInUnitSphere();
        return 0.5f * colourDiffuse( Ray(record.point, target - record.point), world);
    } else { 
        // background colour
        Maths::Vec3 unitDircetion = Maths::normalise(r.direction());
        float t = 0.5f * (unitDircetion.getY() + 1.0f);
        return (1.0f - t) * Maths::Vec3(1.0f, 1.0f, 1.0f) + t * Maths::Vec3(0.5f, 0.7f, 1.0f);
    }
}

//---------------------------------------------------------
Maths::Vec3 colour(Ray const r,  Hitable * world) {
    HitRecord record;

    if(world->hit(r, 0.0f, FLT_MAX, record)) {
        return 0.5f * Maths::Vec3(record.normal.getX() + 1, record.normal.getY() + 1, record.normal.getZ() + 1);
    } else { 
        // background colour
        Maths::Vec3 unitDircetion = Maths::normalise(r.direction());
        float t = 0.5f * (unitDircetion.getY() + 1.0f);
        return (1.0f - t) * Maths::Vec3(1.0f, 1.0f, 1.0f) + t * Maths::Vec3(0.5f, 0.7f, 1.0f);
    }
}

//---------------------------------------------------------
int main(int argc, const char * argv[]) {
    int width  {500};
    int height {250};
    int aaSamples{100};
    std::string outputLocation{"render.ppm"};

    std::ofstream file;
    file.open(outputLocation);

    if(!file.is_open()) {
        std::cout << "\n\nFile failed to open" << std::endl;
        std::cout << "--------------------------------------" << std::endl;
        std::cerr << "file: " << outputLocation << std::endl;
        std::cout << "\n\n" << std::endl;
        return -1;
    }
    
    // typedefs
    typedef std::chrono::system_clock Clock;

    // diognostics variables
    int raysPerSecond = 0;
    int maxRPS        = 0;
    int minRPS        = INT_MAX;
    auto startRender  = Clock::now();
    Camera cam(Maths::Vec3(0, 0, 0));

    // variables needed for render
    
    Hitable * list[4];
   
    list[1] = new Sphere(Maths::Vec3( 0,    0,     -1), 0.5);
    list[2] = new Sphere(Maths::Vec3(-0.5,  0 ,    -1), 0.5);
    list[3] = new Sphere(Maths::Vec3( 0.5,  0,     -1), 0.5);
    list[0] = new Sphere(Maths::Vec3( 0,   -100.5, -1), 100);
    Hitable * world = new HitList(list, 2);

    // string used as a buffer 
    std::string buffer;
    buffer.reserve(width * height);

    int index = 0;
    int percentComplete = 0;
    int onePercent = height / 100;

    std::cout << "\n\nTrace Started" << std::endl;
    std::cout << "-------------" << std::endl; 
    for(int j {height - 1}; j >= 0; j--) {
        index++;
        if(index > onePercent) {
            percentComplete++;
            std::cout << "(" << percentComplete << ")%" << std::endl;
            index = 0;
        }
        for(int i{0}; i < width; i++) {
            Maths::Vec3 col(0,0,0);
            for(int anti = 0; anti < aaSamples; anti++) {
                // trace the scene
                float u = (float)(i + ::randF(0.0f, 1.0f)) / (float)(width);
                float v = (float)(j + ::randF(0.0f, 1.0f)) / (float)(height);
                Ray ray(cam.getRay(u, v));
                //col += ::colour(ray, world);
                col += ::colourDiffuse(ray, world);
            }
            
            col /= float(aaSamples);
            col = Maths::Vec3(sqrtf(col.getX()), sqrtf(col.getY()), sqrtf(col.getZ()));
            int ir {static_cast<int>(255.99 * col.getX())};
            int ig {static_cast<int>(255.99 * col.getY())};
            int ib {static_cast<int>(255.99 * col.getZ())};
            
            // append to buffer
            buffer += std::to_string(ir);
            buffer += " ";
            buffer += std::to_string(ig);
            buffer += " ";
            buffer += std::to_string(ib);
            buffer += "\n";
        }
    }
    auto endRender = std::chrono::system_clock::now();

    file << "P3\n" << width << " " << height << "\n255\n";  
    file << buffer;
    file.close();

    // print diognostics
    std::cout << "\n\nTrace Info" << std::endl;
    std::cout << "-------------" << std::endl;
    std::cout << "Trace time [in milliseconds]: " << std::chrono::duration_cast<std::chrono::milliseconds>(endRender - startRender).count() << "ms"<< std::endl;
    std::cout << "Trace time [in seconds]:      " << std::chrono::duration_cast<std::chrono::seconds>(endRender - startRender).count() << "s"<< std::endl;
    std::cout << "Max RPS [rays per second]:    " << maxRPS << std::endl;
    std::cout << "Min RPS [rays per second]:    " << minRPS << std::endl;
    std::cout << "Total Rays:                   " << width * height * aaSamples << std::endl;
    std::cout << "AA samples:                   " << aaSamples << std::endl;
    return 0;
}
