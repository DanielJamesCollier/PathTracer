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
#include <climits>
#include <cmath>
#include <chrono>
#include <vector>

#include "Vec3.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "Tracer.hpp"
#include "Camera.hpp"

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
    Maths::Vec3 unitDircetion = Maths::normalise(r.direction());
    
    float t = 0.5f * (unitDircetion.getY() + 1.0f);
    
    return (1.0f - t) * Maths::Vec3(1.0f, 1.0f, 1.0f) + t * Maths::Vec3(0.5f, 0.7f, 1.0f);
}

//---------------------------------------------------------
Maths::Vec3 sphereColour(Ray const & r, float t) {
    Maths::Vec3 N = Maths::normalise(r.pointAtParam(t) - Maths::Vec3(0.0f,0.0f,-1.0f));
    return 0.5f * Maths::Vec3(N.getX() + 1.0f, N.getY() + 1.0f, N.getZ() + 1.0f);
}

//---------------------------------------------------------
int main(int argc, const char * argv[]) {
    int width  {2000};
    int height {1000};
    std::string outputLocation{"build\\bin\\output\\render.ppm"};

    std::ofstream file;
    file.open(outputLocation);

    if(!file.is_open()) {
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "File failed to open" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cerr << "file: " << outputLocation << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        return -1;
    }

    std::cout << "\n\n----------------------------------------" << std::endl;
    std::cout << "Trace Started" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    file << "P3\n" << width << " " << height << "\n255\n";    

    typedef std::chrono::system_clock Clock;
    typedef std::chrono::milliseconds milli;

    int raysPerSecond       = 0;
    int maxRPS              = 0;
    int minRPS              = INT_MAX;
    int percentRendered     = 0;
    int onePercent          = (width * height) / 100;
    int currentItt          = 0;
    auto startRender        = Clock::now();
    auto startSecondCounter = Clock::now();
    Camera cam(Maths::Vec3(0,0,0));
    Sphere sphere(Maths::Vec3(0,0,-1),0.5f);

    for(int j {height - 1}; j >= 0; j--) {
        for(int i{0}; i < width; i++) {
            auto currentTime = Clock::now();
            auto duration    = std::chrono::duration_cast<milli>(currentTime - startSecondCounter);
            raysPerSecond++;
            currentItt++;

            // calculate percent rendered
            if(currentItt > onePercent) {
                percentRendered++;
                currentItt = 0;
            }

            // calculate RPS
            if(duration > milli(1000)) {
                std::cout << "tracing..." << percentRendered << "%" << " - RPS: " << raysPerSecond << std::endl;
                if(raysPerSecond > maxRPS) maxRPS = raysPerSecond;
                if(raysPerSecond < minRPS) minRPS = raysPerSecond;
                raysPerSecond = 0;
                startSecondCounter = Clock::now();
            }
            
            float u = (float)(i) / (float)(width);
            float v = (float)(j) / (float)(height);
            
            Ray ray = cam.getRay(u, v);
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
    
    auto endRender = std::chrono::system_clock::now();
    std::cout << "----------------------------------------" << std::endl;
    
    file.close();

    std::cout << "\n\n----------------------------------------" << std::endl;
    std::cout << "Trace Info" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Trace time [in milliseconds]: " << std::chrono::duration_cast<std::chrono::milliseconds>(endRender - startRender).count() << "ms"<< std::endl;
    std::cout << "Trace time [in seconds]:      " << std::chrono::duration_cast<std::chrono::seconds>(endRender - startRender).count() << "s"<< std::endl;
    std::cout << "Max RPS [rays per second]:    " << maxRPS << std::endl;
    std::cout << "Min RPS [rays per second]:    " << minRPS << std::endl;
    std::cout << "Total Rays:                   " << width * height << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    return 0;
}
