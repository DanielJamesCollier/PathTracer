//
//  main.cpp
//  PathTracer
//
//  Created by Daniel Collier on 10/01/2017.
//  Copyright © 2017 Daniel Collier. All rights reserved.
//


// own
#include "Ray.hpp"
#include "Camera.hpp"
#include "Utils.hpp"
#include "Scene.hpp"
#include "SDL_Module.hpp"
#include "MutexPrint.hpp"
#include "Tracer.hpp"

// djc_math
#include "djc_math/Vec3.hpp"

// std
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
#include <algorithm>
#include <thread>
#include <future>
#include <mutex>


// defines
//----------------------------------------
#define WRITE_OUTPUT_TO_FILE
#define RUN_ASYNC

// aliases
//----------------------------------------
using namespace std::string_literals;
using Clock = std::chrono::high_resolution_clock;
using PixelStorage = std::vector<std::vector<djc_math::Vec3f>>;

// globals
//----------------------------------------
std::mutex g_pixelWrite;

//---------------------------------------------------------
bool writeToFile(std::string fileLocation, int width, int height, int samples, PixelStorage & pixels) {
    std::ofstream file;
    file.open(fileLocation);

    // early return
    if(!file.is_open()) {
        std::cerr << "\n\nFile failed to open\n";
        std::cerr << "--------------------------------------\n";
        std::cerr << "file: " << fileLocation << "\n";
        std::cerr << "\n\n";
        return false;
    }

    // intialise the string buffer with the .ppm header
    std::string buffer = "P3\n" + std::to_string(width) + " " + std::to_string(height) + "\n255\n";

    for(auto y = height - 1; y > 0; y--) { 
        for(auto x = 0; x < width; x++) {  
            djc_math::Vec3f & pixel = pixels[y][x];
            pixel /= static_cast<float>(samples);
            pixel = djc_math::Vec3f(sqrtf(pixel.x), sqrtf(pixel.y), sqrtf(pixel.z));
            int ir = static_cast<int>(255.99 * pixel.x);
            int ig = static_cast<int>(255.99 * pixel.y);
            int ib = static_cast<int>(255.99 * pixel.z);

            std::string rgb_string = std::to_string(ir) + " " + std::to_string(ig) + " " + std::to_string(ib) + "\n";
            buffer += rgb_string;
        }
    }
    file << buffer;
    std::cout << fileLocation << " written to disk\n" << std::flush;
    return true;
}

//---------------------------------------------------------
void 
writePixelsOutOfThread(PixelStorage & screenPixels, PixelStorage const & threadLocalPixels, std::size_t location) {
    std::lock_guard<std::mutex> m(g_pixelWrite);    
    std::copy_n(threadLocalPixels.begin(), threadLocalPixels.size(), &screenPixels[location]);
}

//---------------------------------------------------------
int main(int argc, char* argv[])  {
    std::cout << "\n-----------------------------\n";
    std::cout << "Program: Path Tracer\n";
    std::cout << "Programmer: Daniel James Collier\n";
    std::cout << "-----------------------------\n\n";

    // image specification
	//------------------------
    constexpr auto width      = 384;
    constexpr auto height     = width * 9 / 16;
    constexpr auto aspect     = static_cast<float>(width) / static_cast<float>(height);
    constexpr auto maxSamples = 1;

    const auto outputLocation = "./render.ppm"s;
    bool running = true;

    SDL_Module sdl("PathTracer", width, height);
    Camera cam(djc_math::Vec3f(0,0,3), 70, aspect);

    // resize the pixel vector so it has the storage for [height][width]
    PixelStorage pixels;
    pixels.resize(height);
    for (auto && row : pixels) {
        row.resize(width);
    }

    // materials -- S= soft | R = reflective
	//------------------------
    auto metalS         = std::make_unique<Metal>(djc_math::Vec3f(0.8f, 0.8f, 0.8f), 1.0f);
    auto metalR         = std::make_unique<Metal>(djc_math::Vec3f(0.8f, 0.6f, 0.2f), 0.1f);
    auto glass          = std::make_unique<Dialectric>(1.5f);
    auto metal_RoseGold = std::make_unique<Metal>(djc_math::Vec3f(0.71484375f, 0.4296875f, 0.47265625f), 0.1f);
    auto lambert        = std::make_unique<Lambertian>(djc_math::Vec3f(0.8f, 0.3f, 0.3f));

    // add spheres to world
    
	//------------------------
    Scene world;
    world.addSphere(djc_math::Vec3f(0, -100.5, -1), 100, &*metal_RoseGold);
    world.addSphere(djc_math::Vec3f(0, 2.5, -8), 3, &*metal_RoseGold);  // ball at back 
    world.addSphere(djc_math::Vec3f( 2, 0, -1), 0.5, &*metal_RoseGold); // right
    world.addSphere(djc_math::Vec3f( 1, 0, -1), 0.5, &*lambert);        // middle right
    world.addSphere(djc_math::Vec3f(-2, 0, -1), 0.5, &*metal_RoseGold); // left
    world.addSphere(djc_math::Vec3f(-1, 0, -1), 0.5, &*lambert);        // middle left
    world.addSphere(djc_math::Vec3f( 0, 0, -1), 0.5, &*glass);          // middle ball

     auto singleThreaded = [&]() {
        std::cout << "Log\n";
        std::cout << "-----------------------------\n";
        std::cout << "multiple threads not detected. running single threaded\n";
        TraceTaskRange taskRangeOne(0, width, 0, height);
        TraceTask taskOne(taskRangeOne, maxSamples, world, cam, width, height);

        auto begin = Clock::now();

        auto donePixels = taskOne();
        pixels = donePixels;

        auto end = Clock::now();
        auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        std::cout << "total time: " << passed << "ms\n";
        std::cout << "samples: " << maxSamples << "\n\n";
    };
   

#   if defined(RUN_ASYNC) 
    {
        auto threadCount = std::thread::hardware_concurrency(); // can return 0 in some cases
        if(threadCount == 0) threadCount = 1;

        if(threadCount >= 2) {
            threadCount -= 1; // if computer has 4 threads launch 3 because main thread means 4 will be running
            std::cout << "Log\n";
            std::cout << "-----------------------------\n";
            std::cout << "threads: " << threadCount << " for tracing + 1 main thread\n";

            std::vector<std::future<PixelStorage>> futurePixels;
            futurePixels.reserve(threadCount);

            int heightStep = height / threadCount;
            int currentStep = heightStep;
            int lastStep = heightStep;

            TraceTaskRange rangeOne(0, width, 0, currentStep);
            TraceTask taskOne(rangeOne, maxSamples, world, cam, width, height);
            futurePixels.push_back(std::async(std::launch::async, taskOne)); // launch trace in another thread
         
            for (int i = 0; i < threadCount; i ++) {

                currentStep += heightStep;

                TraceTaskRange rangeOne(0, width, lastStep, currentStep);

                TraceTask taskOne(rangeOne, maxSamples, world, cam, width, height);
                futurePixels.push_back(std::async(std::launch::async, taskOne)); // launch trace in another thread
                
                lastStep = currentStep;
            }

            auto begin = Clock::now();

            currentStep = 0;   
            // wait for the thread finish copying the local pixels into the main pixel array
            for (int i = 0; i < threadCount; i++) {
                writePixelsOutOfThread(pixels, futurePixels[i].get(), currentStep); // block until trace is done
                currentStep += heightStep;
            }

            auto end = Clock::now();
            auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
            std::cout << "total time: " << passed << "ms\n";
            std::cout << "samples: " << maxSamples << "\n\n";
            
        } else {
            singleThreaded();
        }
    }
#   else // run single threaded
    {
        singleThreaded();
    }
#   endif

    while (running) {
        sdl.eventLoop(running);
        sdl.draw(pixels, maxSamples);
    }
    
#   if defined(WRITE_OUTPUT_TO_FILE)
        if(!::writeToFile(outputLocation, width, height, maxSamples, pixels)) {
                return -1;
        }
#   endif

    return 0;
}
