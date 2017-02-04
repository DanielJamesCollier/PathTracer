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
#include <array>
#include <memory>
#include <cassert>
#include <thread>

#include "Vec3.hpp"
#include "Ray.hpp"
#include "Camera.hpp"
#include "Utils.hpp"
#include "Scene.hpp"
#include "Window.hpp"
#include "MultiArray.hpp"

using namespace std::string_literals;

#define RAY_DEPTH 100

//---------------------------------------------------------
Maths::Vec3 colour(Ray const r,  Scene const & world, int depth) {
    HitRecord record;

    if(world.hit(r, 0.001f, std::numeric_limits<float>::max(), record)) {
        assert(record.ptr_mat != nullptr);
        Ray scattered;
        Maths::Vec3 attenuation;

        if(depth < RAY_DEPTH && record.ptr_mat->scatter(r, record, /*out var*/ attenuation, /*out var*/ scattered)) {
            return attenuation * colour(scattered, world, depth + 1);
        } else {
            return Maths::Vec3(0, 0, 0);
        }
    } else { 
        // background colour
        Maths::Vec3 unitDircetion = Maths::normalise(r.direction());
        auto t = 0.5f * (unitDircetion.getY() + 1.0f);
        return (1.0f - t) * Maths::Vec3(1.0f, 1.0f, 1.0f) + t * Maths::Vec3(0.5f, 0.7f, 1.0f);
    }
}

//---------------------------------------------------------
template<int width, int height>
bool writeToFile(std::string fileLocation,int samples, MultiArray<Maths::Vec3, width, height> & pixels) {
    std::ofstream file;
    file.open(fileLocation);

    // early return
    if(!file.is_open()) {
        std::cout << "\n\nFile failed to open" << std::endl;
        std::cout << "--------------------------------------" << std::endl;
        std::cerr << "file: " << fileLocation << std::endl;
        std::cout << "\n\n" << std::endl;
        return false;
    }

    // intialise the string buffer with the .ppm header
    std::string buffer = "P3\n" + std::to_string(width) + " " + std::to_string(height) + "\n255\n";

    // convert pixel array into string array
    for(auto j = height; j > 0; j--) {
            for(auto i = 0; i < width; i++) {
                pixels(i,j) /= static_cast<float>(samples);
                pixels(i, j) = Maths::Vec3(sqrtf(pixels(i, j).getX()), sqrtf(pixels(i, j).getY()), sqrtf(pixels(i, j).getZ()));
                int ir = static_cast<int>(255.99 * pixels(i, j).getX());
                int ig = static_cast<int>(255.99 * pixels(i, j).getY());
                int ib = static_cast<int>(255.99 * pixels(i, j).getZ());
        
                std::string rgb_string = std::to_string(ir) + " " + std::to_string(ig) + " " + std::to_string(ib) + "\n";
                buffer += rgb_string;
        }
    }
    file << buffer;
    return true;
}

//---------------------------------------------------------
int main(int argc, char* argv[])  {
    // multithreading stuff
    auto numCores =  std::thread::hardware_concurrency();

    // some times we cant detect the number of cores on a machine,
    // if we cant just run single threaded
    if(numCores == 1) {
        numCores = 2;
    }

    std::cout << "Cores Available: " << numCores << std::endl;
    std::cout << "Spooling Cores..." << std::endl;
    //...

    // image specification
    const int x = 100;
    const int y = 100;
    const int width = 1000;
    const int height = 400;
    const int maxSamples = 2000;
    const auto outputLocation = "./render.ppm"s;
    //...

    // materials
    auto lambertFloor = std::make_unique<Lambertian>(Maths::Vec3(0.8f, 0.8f, 0.0f));
    auto lambertMiddle = std::make_unique<Lambertian>(Maths::Vec3(0.8f, 0.3f, 0.3f));
    auto leftMetal = std::make_unique<Metal>(Maths::Vec3(0.8f, 0.8f, 0.8f), 1.0f);
    auto rightMetal = std::make_unique<Metal>(Maths::Vec3(0.8f, 0.6f, 0.2f), 0.1f);
    auto glass = std::make_unique<Dialectric>(1.5f);
    //...

    // add spheres to world
    Scene world;
    world.addSphere(Maths::Vec3(0, -100.5, -1), 100, &*lambertFloor);
    world.addSphere(Maths::Vec3(1, 2.5, -8), 3, &*rightMetal); 
    world.addSphere(Maths::Vec3(2, 0, -1), 0.5, &*rightMetal);
    world.addSphere(Maths::Vec3(1, 0, -1), 0.5, &*leftMetal);
    world.addSphere(Maths::Vec3(-1, 0, -1), 0.5,&*glass);  
    world.addSphere(Maths::Vec3(0, 0, -1), 0.5, &*lambertMiddle); 
    //...
   
    // used to print diagonostics
    auto index = 0;
    auto percentComplete = 0;
    auto onePercent = (width * height * maxSamples) / 100;
    //...

    // render critial variables
    Window window("PathTracer", x, y, width, height);
    Camera cam(Maths::Vec3(0,0,4), 70, (float) width / (float)height);
    MultiArray<Maths::Vec3, width, height> pixels;
    bool running = true;
    auto currentSamples = 0;
    using Clock = std::chrono::system_clock;
    //..

    std::cout << "\n\nTrace Started" << std::endl;
    std::cout << "-------------" << std::endl; 
    
    int forward = 0; // used to flip the image for sdl drawing
    auto startRender = Clock::now();

    for(auto s = 0; s < maxSamples; s++) {
        for(auto j = height, forward = 0; j > 0; j--, forward++) { 
            for(auto i = 0; i < width; i++) {
                auto u = (float)(i + Utils::randF()) / (float)(width);
                auto v = (float)(j + Utils::randF()) / (float)(height);
                Ray ray(cam.getRay(u, v));
                pixels(i,j) += ::colour(ray, world, 0);

                // draw current pixel to screen
                Maths::Vec3  temp = pixels(i,j);
                temp /= s + 1;
                temp = Maths::Vec3(sqrtf(temp.getX()), sqrtf(temp.getY()), sqrtf(temp.getZ()));
                int ir = static_cast<int>(255.99 * temp.getX());
                int ig = static_cast<int>(255.99 * temp.getY());
                int ib = static_cast<int>(255.99 * temp.getZ());
                window.output(ir, ig, ib, i, forward);
                //...

                // calculate and print percentage complete
                index++;
                if(index > onePercent) {
                    index = 0;
                    std::cout << "(" << percentComplete << ")%" << std::endl;
                    percentComplete++;
                }
                //...
            }
        }
        window.swapBackBuffer();

        // check if the window has been closed
        window.eventLoop(running);
        if(!running) {
            currentSamples = s + 1;
            break;
        }
        //...
    }
    auto endRender = std::chrono::system_clock::now();

    // output file 
    if(running) {
        if(!::writeToFile(outputLocation, maxSamples, pixels)) return -1;
    } else {
        if(!::writeToFile(outputLocation, currentSamples, pixels)) return -1;
    }
    //...

    // print diognostics
    std::cout << "\n\nTrace Info" << std::endl;
    std::cout << "-------------" << std::endl;
    std::cout << "Trace time [in milliseconds]: " << std::chrono::duration_cast<std::chrono::milliseconds>(endRender - startRender).count() << "ms"<< std::endl;
    std::cout << "Trace time [in seconds]:      " << std::chrono::duration_cast<std::chrono::seconds>(endRender - startRender).count() << "s"<< std::endl;
    std::cout << "Total Rays:                   " << width * height * currentSamples << std::endl;
    std::cout << "Samples:                      " << currentSamples << std::endl;
    std::cout << "Samples Per Second            " << static_cast<float>(currentSamples) / static_cast<float>(std::chrono::duration_cast<std::chrono::seconds>(endRender - startRender).count()) << std::endl;
    //...
    return 0;
}
