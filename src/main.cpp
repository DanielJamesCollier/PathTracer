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
#include <random>

#include "Vec3.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"

//---------------------------------------------------------
void backgroundColour(Ray const & r, Maths::Vec3 & colour) {
    Maths::Vec3 unitDircetion = Maths::normalise(r.direction());
    float t = 0.5f * (unitDircetion.getY() + 1.0f);
    colour = (1.0f - t) * Maths::Vec3(1.0f, 1.0f, 1.0f) + t * Maths::Vec3(0.5f, 0.7f, 1.0f);
}

//---------------------------------------------------------
int main(int argc, const char * argv[]) {
    int width  {1000};
    int height {500};
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

    std::cout << "\n\nTrace Started" << std::endl;
    std::cout << "-------------" << std::endl;
    file << "P3\n" << width << " " << height << "\n255\n";    

    typedef std::chrono::system_clock Clock;
    typedef std::chrono::milliseconds milli;
    typedef std::uniform_real_distribution<float> randGen;

    int raysPerSecond       = 0;
    int maxRPS              = 0;
    int minRPS              = INT_MAX;
    int percentRendered     = 0;
    int onePercent          = (width * height) / 100;
    int currentItt          = 0;
    auto startRender        = Clock::now();
    auto startSecondCounter = Clock::now();
    Camera cam(Maths::Vec3(0, 0, 0));

    std::vector<Sphere> spheres;
    spheres.push_back(Sphere(Maths::Vec3(0, -100.5, -1), 100));
    spheres.push_back(Sphere(Maths::Vec3(0, 0, -1), 0.5f));

    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<> distr(0.0f, 1.0f);
    Maths::Vec3 col(0, 0 ,0);

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
                    if (percentRendered > 10) {
                        std::cout << "tracing... (" << percentRendered << "%)" << " - RPS: " << raysPerSecond << std::endl;
                    } else {
                        std::cout << "tracing... (" << percentRendered << "%) " << " - RPS: " << raysPerSecond << std::endl;
                    }
                    
                    if(raysPerSecond > maxRPS) maxRPS = raysPerSecond;
                    if(raysPerSecond < minRPS) minRPS = raysPerSecond;
                    raysPerSecond = 0;
                    startSecondCounter = Clock::now();
                }

                for(int aa = 0; aa < aaSamples; aa++) {
                    float u = (float)(i + distr(generator)) / (float)(width);
                    float v = (float)(j + distr(generator)) / (float)(height);
                    
                    Ray ray(cam.getRay(u, v));

                    backgroundColour(ray, col);
              
                     // this could be optimized to only be called if no spheres are present
                    bool drawBackground = false;
                    for(Sphere & s : spheres) {
                        drawBackground = !s.trace(ray, col);
                    }

                    if(drawBackground) {
                       
                    }
                }

                //col /= float(aaSamples);
                
                int ir {static_cast<int>(255.99 * col.getX())};
                int ig {static_cast<int>(255.99 * col.getY())};
                int ib {static_cast<int>(255.99 * col.getZ())};
                
                file << ir << " " << ig << " " << ib << "\n";
        }
    }
    
    auto endRender = std::chrono::system_clock::now();
    
    file.close();

    std::cout << "\n\nTrace Info" << std::endl;
    std::cout << "-------------" << std::endl;
    std::cout << "Trace time [in milliseconds]: " << std::chrono::duration_cast<std::chrono::milliseconds>(endRender - startRender).count() << "ms"<< std::endl;
    std::cout << "Trace time [in seconds]:      " << std::chrono::duration_cast<std::chrono::seconds>(endRender - startRender).count() << "s"<< std::endl;
    std::cout << "Max RPS [rays per second]:    " << maxRPS << std::endl;
    std::cout << "Min RPS [rays per second]:    " << minRPS << std::endl;
    std::cout << "Total Rays:                   " << width * height << std::endl;
    std::cout << "Total Spheres:                " << spheres.size() << std::endl;
    std::cout << "AA samples:                   " << aaSamples << std::endl;
    std::cout << "\n\n" << std::endl;
    return 0;
}
