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

#include "Vec3.hpp"
#include "Ray.hpp"
#include "Camera.hpp"
#include "Utils.hpp"
#include "Scene.hpp"

using namespace std::string_literals;

//---------------------------------------------------------
//#include "Material.hpp"
Maths::Vec3 colour(Ray const r,  Scene const & world, int depth) {
    HitRecord record;

    if(world.hit(r, 0.001f, std::numeric_limits<float>::max(), record)) {
        assert(record.ptr_mat != nullptr);
        Ray scattered;
        Maths::Vec3 attenuation;

        if(depth < 50 && record.ptr_mat->scatter(r, record, /*out var*/ attenuation, /*out var*/ scattered)) {
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
int main(int argc, const char * argv[]) {
    auto width = 2000;
    auto height = 1000;
    auto pixelComponents = 3;
    auto aaSamples = 100;
    auto outputLocation = "./render.ppm"s;

    std::ofstream file;
    file.open(outputLocation);

    if(!file.is_open()) {
        std::cout << "\n\nFile failed to open" << std::endl;
        std::cout << "--------------------------------------" << std::endl;
        std::cerr << "file: " << outputLocation << std::endl;
        std::cout << "\n\n" << std::endl;
        return -1;
    }
    
    //alias
    using Clock = std::chrono::system_clock;

    // diognostics variables
    auto startRender = Clock::now();
    Camera cam(Maths::Vec3(0, 0, 0));

    // variables needed for render
    Scene world;
    world.addSphere(Maths::Vec3(0, -100.5, -1), 100, new Lambertian(Maths::Vec3(0.8,0.8,0.0))); // floor

    world.addSphere(Maths::Vec3(1, 0, -1), 0.5, new Metal(Maths::Vec3(0.8 ,0.8, 0.8), 0.3f));           // right
    world.addSphere(Maths::Vec3(-1, 0, -1), 0.5, new Metal(Maths::Vec3(0.8 ,0.8, 0.8), 1.0f));          // left
    world.addSphere(Maths::Vec3(0, 0, -1), 0.5, new Lambertian(Maths::Vec3(0.8,0.3,0.3)));      // middle

    // string used as a buffer 
    std::string buffer;
    buffer.resize(width * height * pixelComponents);

    // used to print diagonostics
    auto index = 0;
    auto percentComplete = 0;
    auto onePercent = (width * height * aaSamples) / 100 + 1;

    std::cout << "\n\nTrace Started" << std::endl;
    std::cout << "-------------" << std::endl; 
    for(auto j = height; j > 0; j--) {
        for(auto i = 0; i < width; i++) {
            Maths::Vec3 col(0,0,0);
            for(auto anti = 0; anti < aaSamples; anti++) {
                // trace the scene
                auto u = float{(float)(i + Utils::randF()) / (float)(width)};
                auto v = float{(float)(j + Utils::randF()) / (float)(height)};
                Ray ray(cam.getRay(u, v));
                col += ::colour(ray, world, 0);

                // calculate and print percentage complete
                index++;
                if(index > onePercent) {
                    index = 0;
                    std::cout << "(" << percentComplete << ")%" << std::endl;
                    percentComplete++;
                }
            }
            
            col /= float(aaSamples);
            col = Maths::Vec3(sqrtf(col.getX()), sqrtf(col.getY()), sqrtf(col.getZ()));
            auto ir = static_cast<int>(255.99 * col.getX());
            auto ig = static_cast<int>(255.99 * col.getY());
            auto ib = static_cast<int>(255.99 * col.getZ());
    
            buffer += std::to_string(ir) + " " + std::to_string(ig) + " " + std::to_string(ib) + "\n";
        }
    }
    auto endRender = std::chrono::system_clock::now();

    file << "P3\n" << width << " " << height << "\n255\n";  
    file << buffer;

    // print diognostics
    std::cout << "\n\nTrace Info" << std::endl;
    std::cout << "-------------" << std::endl;
    std::cout << "Trace time [in milliseconds]: " << std::chrono::duration_cast<std::chrono::milliseconds>(endRender - startRender).count() << "ms"<< std::endl;
    std::cout << "Trace time [in seconds]:      " << std::chrono::duration_cast<std::chrono::seconds>(endRender - startRender).count() << "s"<< std::endl;
    std::cout << "Total Rays:                   " << width * height * aaSamples << std::endl;
    std::cout << "AA samples:                   " << aaSamples << std::endl;
    return 0;
}
