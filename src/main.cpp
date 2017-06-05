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
#include "Usings.hpp"
#include "MutexPrint.hpp"

using namespace std::string_literals;
using Clock = std::chrono::high_resolution_clock;



#define RAY_DEPTH 50

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
template<size_t width, size_t height>
bool writeToFile(std::string fileLocation,int samples, Usings::Array2D<Maths::Vec3, width, height> & pixels) {
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

    for(auto y = height - 1; y > 0; y--) { 
        for(auto x = 0; x < width; x++) {  
            Maths::Vec3 & pixel = pixels[y][x];
            pixel /= static_cast<float>(samples);
            pixel = Maths::Vec3(sqrtf(pixel.getX()), sqrtf(pixel.getY()), sqrtf(pixel.getZ()));
            int ir = static_cast<int>(255.99 * pixel.getX());
            int ig = static_cast<int>(255.99 * pixel.getY());
            int ib = static_cast<int>(255.99 * pixel.getZ());

            std::string rgb_string = std::to_string(ir) + " " + std::to_string(ig) + " " + std::to_string(ib) + "\n";
            buffer += rgb_string;
        }
    }
    file << buffer;
    std::cout << fileLocation << " written to disk" << std::endl;
    return true;
}

//---------------------------------------------------------
template<int ScreenWidth, int ScreenHeight>
struct TraceJob {
    TraceJob(int id, int xBegin, int yBegin, int xEnd, int yEnd, int samples, Camera const & camera, Scene const & scene, Usings::Array2D<Maths::Vec3, ScreenWidth, ScreenHeight> & pixels, bool & running) :
        m_id(id)
    ,   m_xBegin(xBegin)
    ,   m_yBegin(yBegin)
    ,   m_xEnd(xEnd)
    ,   m_yEnd(yEnd)
    ,   m_samples(samples)
    ,   m_camera(camera)
    ,   m_scene(scene)
    ,   m_pixels(pixels)
    ,   m_running(running)
    {
        // empty
    }
    
    void operator() () {
        MutexPrint{} << "[" << m_id << "]Thread launched" << std::endl;
        for(auto s = 0; s < m_samples; s++) {
            if(!m_running) {
                MutexPrint{} << "[" << m_id << "]Thread termined before finished" << std::endl;
                return;
            }
            
           

		    for(auto y = m_yBegin; y < m_yEnd; y++) { 
                for(auto x = m_xBegin; x < m_xEnd; x++) {     
		            auto u = (float)(x + Utils::randF()) / (float)(ScreenWidth);
                    auto v = (float)(y + Utils::randF()) / (float)(ScreenHeight);
                    Ray ray(m_camera.getRay(u, v));
                    m_pixels[y][x] += ::colour(ray, m_scene, 0); //@TODO : y and x wrong way ?
                }
            }
        }
        MutexPrint{} << "[" << m_id << "]Thread finished" << std::endl;
    }

private:
    int m_id;
    int m_xBegin;
    int m_yBegin;
    int m_xEnd;
    int m_yEnd;
    int m_samples;
    Camera m_camera;
    Scene const & m_scene;
    Usings::Array2D<Maths::Vec3, ScreenWidth, ScreenHeight> & m_pixels;
    bool & m_running;
};

//---------------------------------------------------------
int main(int argc, char* argv[])  {
    std::cout << "-----------------------------\n";
    std::cout << "Program: Path Tracer\n";
    std::cout << "Programmer: Daniel James Collier\n";
    std::cout << "-----------------------------\n";

    // image specification
	//------------------------
    const int x          = 0; // x: 0 - y: 0 seems to make the window border get cut off -_-
    const int y          = 20;
    const int width      = 500; //@Todo: make sure width and height are divisable by two aka even
    const int height     = width * 9 / 16;
    const int maxSamples = 20;
    const auto outputLocation = "./render.ppm"s;
    bool running = true;

    Window window("PathTracer", x, y, width, height);
    Usings::Array2D<Maths::Vec3, width, height> pixels;
    Camera cam(Maths::Vec3(0,0,3), 70, (float) width / (float)height);


    // materials -- S= soft | R = reflective
	//------------------------
    auto metalS         = std::make_unique<Metal>(Maths::Vec3(0.8f, 0.8f, 0.8f), 1.0f);
    auto metalR         = std::make_unique<Metal>(Maths::Vec3(0.8f, 0.6f, 0.2f), 0.1f);
    auto glass          = std::make_unique<Dialectric>(1.5f);
    auto metal_RoseGold = std::make_unique<Metal>(Maths::Vec3(0.71484375f, 0.4296875f, 0.47265625f), 0.1f);
    auto lambert        = std::make_unique<Lambertian>(Maths::Vec3(0.8f, 0.3f, 0.3f));

    // add spheres to world
    
	//------------------------
    Scene world;
    world.addSphere(Maths::Vec3(0, -100.5, -1), 100, &*metal_RoseGold);
    world.addSphere(Maths::Vec3(0, 2.5, -8), 3, &*metal_RoseGold); // ball at back 

    world.addSphere(Maths::Vec3(2, 0, -1), 0.5, &*metal_RoseGold);         // right
    world.addSphere(Maths::Vec3(1, 0, -1), 0.5, &*lambert);     // middle right
    world.addSphere(Maths::Vec3(-2, 0, -1), 0.5,&*metal_RoseGold);     // left
    world.addSphere(Maths::Vec3(-1, 0, -1), 0.5,&*lambert);         // middle left
    world.addSphere(Maths::Vec3(0, 0, -1), 0.5, &*glass); // middle ball
	
	// render
	//------------------------
    auto logicalCoreCount = std::thread::hardware_concurrency();

    // if cannot dettect core count set to one
    if(logicalCoreCount == 0) {
        logicalCoreCount = 1;
    }

    std::cout << "Cores Available: " << logicalCoreCount << "\nMain Thread running...\n";

    std::vector<std::thread> traceJobs;

    // force single threaded
    logicalCoreCount = 1;

    if(logicalCoreCount == 1) { // @Fix: this would mean that two threads are running - main thread & one trace thread
            TraceJob<width, height> job(1, 0, 0, width, height, maxSamples, cam, world, pixels, running);
            traceJobs.push_back(std::thread(job));
    } else  {
        logicalCoreCount -= 1; // if 4 cores available, launch 3 trace threads, 3 trace + 1 main = 4 total
        for(int i = 0; i < logicalCoreCount; i++) {
            if(i == 0) {
                TraceJob<width, height> job(i, 0, 0, width, height / logicalCoreCount, maxSamples, cam, world, pixels, running);
                traceJobs.push_back(std::thread(job));
            } else {
                TraceJob<width, height> job(i, 0, height * ((float)i / (float)logicalCoreCount), width, height * ((float)(i + 1.0f) / (float)logicalCoreCount), maxSamples, cam, world, pixels, running);
                traceJobs.push_back(std::thread(job));
            }
        }
    }

    while(running) {
        window.eventLoop(running);
        window.draw(pixels, maxSamples);
    }
    
    for(auto & job : traceJobs) {
        job.join();
    }
	
    if(!::writeToFile(outputLocation, maxSamples, pixels)) {
			return -1;
	}

    return 0;
}
