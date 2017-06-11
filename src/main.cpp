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
#include "Window.hpp"
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
//#define WRITE_OUTPUT_TO_FILE
#define RUN_ASYNC

// aliases
//----------------------------------------
using namespace std::string_literals;
using Clock = std::chrono::high_resolution_clock;

// globals
//----------------------------------------
std::mutex g_pixelWrite;

//---------------------------------------------------------
bool writeToFile(std::string fileLocation, int width, int height, int samples, std::vector<std::vector<djc_math::Vec3f>> & pixels) {
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
writePixelsOutOfThread(std::vector<std::vector<djc_math::Vec3f>> & screenPixels, std::vector<std::vector<djc_math::Vec3f>> const & threadLocalPixels, std::size_t location) {
    std::lock_guard<std::mutex> m(g_pixelWrite);    
    std::copy_n(threadLocalPixels.begin(), threadLocalPixels.size(), &screenPixels[location]);
}

//---------------------------------------------------------
int main(int argc, char* argv[])  {
    std::cout << "-----------------------------\n";
    std::cout << "Program: Path Tracer\n";
    std::cout << "Programmer: Daniel James Collier\n";
    std::cout << "-----------------------------\n";

    // image specification
	//------------------------
    constexpr auto width      = 1024;
    constexpr auto height     = width * 9 / 16;
    constexpr auto aspect     = static_cast<float>(width) / static_cast<float>(height);
    constexpr auto maxSamples = 1;

    const auto outputLocation = "./render.ppm"s;
    bool running = true;

    Window window("PathTracer", width, height);
    Camera cam(djc_math::Vec3f(0,0,3), 70, aspect);

    // resize the pixel vector so it has the storage for [height][width]
    std::vector<std::vector<djc_math::Vec3f>> pixels;
    pixels.resize(height);
    for (int i = 0; i < height; i++) {
        pixels[i].resize(width);
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

#   if defined(RUN_ASYNC) 
{
     auto begin = Clock::now();
    /*
        /Performance/

        - addidng an extra thread seems to reduce the time by 200ms
    */

    // thread one
    TraceTaskRange taskRangeOne(0, width, 0, height / 2);
    TraceTask taskOne(taskRangeOne, maxSamples, world, cam, width, height);
    auto taskOnePixels = std::async(std::launch::async, taskOne);

    // thread two
    TraceTaskRange taskRangeTwo(0, width, height / 2, height);
    TraceTask taskTwo(taskRangeTwo, maxSamples, world, cam, width, height);
    auto taskTwoPixels = std::async(std::launch::async, taskTwo);

    // thread three
    // TraceTaskRange taskRangeThree(0, width, height / 2, height);
    // TraceTask taskThree(taskRangeThree, maxSamples, world, cam, width, height);
    // auto taskThreePixels = std::async(std::launch::async, taskTwo);
   

    // block this thread and wait until the pixels are rendered
    writePixelsOutOfThread(pixels, taskOnePixels.get(), 0);
    writePixelsOutOfThread(pixels, taskTwoPixels.get(), height / 2);

    auto end = Clock::now();

    auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    std::cout << "total time: " << passed << "ms\n";
    std::cout << "samples: " << maxSamples << "\n";
}
#   else // run single threaded
{
    TraceTaskRange taskRangeOne(0, width, 0, height);
    TraceTask taskOne(taskRangeOne, maxSamples, world, cam, width, height);

    /*
        /Performance Test/
        
        time per sample: 756ms 
        linear scale: yes
        thread count: 1
    */
    auto begin = Clock::now();

    auto donePixels = taskOne();
    pixels = donePixels;
    
    auto end = Clock::now();
    auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    std::cout << "total time: " << passed << "ms\n";
    std::cout << "samples: " << maxSamples << "\n";

    
    std::cout << "done\n";
}
#   endif

    while (running) {
        window.eventLoop(running);
        window.draw(pixels, maxSamples);
    }
    
#   if defined(WRITE_OUTPUT_TO_FILE)
        if(!::writeToFile(outputLocation, width, height, maxSamples, pixels)) {
                return -1;
        }
#   endif

    return 0;
}
