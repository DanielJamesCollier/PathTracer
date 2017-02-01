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

#include "Vec3.hpp"
#include "Ray.hpp"
#include "Camera.hpp"

#include "Scene.hpp"

using namespace std::string_literals;

// lookup table for int to string conversion - faster than std::to_string
//---------------------------------------------------------
std::array<std::string, 256> lookup = {
"0"  , "1"  , "2"  , "3"  , "4"  , "5"  , "6"  , "7"  , "8"  , "9"  , "10" , "11" , "12" , "13" , "14", 
"15" , "16" , "17" , "18" , "19" , "20" , "21" , "22" , "23" , "24" , "25" , "26" , "27" , "28" , "29", 
"30" , "31" , "32" , "33" , "34" , "35" , "36" , "37" , "38" , "39" , "40" , "41" , "42" , "43" , "44", 
"45" , "46" , "47" , "48" , "49" , "50" , "51" , "52" , "53" , "54" , "55" , "56" , "57" , "58" , "59", 
"60" , "61" , "62" , "63" , "64" , "65" , "66" , "67" , "68" , "69" , "70" , "71" , "72" , "73" , "74", 
"75" , "76" , "77" , "78" , "79" , "80" , "81" , "82" , "83" , "84" , "85" , "86" , "87" , "88" , "89", 
"90" , "91" , "92" , "93" , "94" , "95" , "96" , "97" , "98" , "99" , "100", "101", "102", "103", "104", 
"105", "106", "107", "108", "109", "110", "111", "112", "113", "114", "115", "116", "117", "118", "119", 
"120", "121", "122", "123", "124", "125", "126", "127", "128", "129", "130", "131", "132", "133", "134", 
"135", "136", "137", "138", "139", "140", "141", "142", "143", "144", "145", "146", "147", "148", "149", 
"150", "151", "152", "153", "154", "155", "156", "157", "158", "159", "160", "161", "162", "163", "164", 
"165", "166", "167", "168", "169", "170", "171", "172", "173", "174", "175", "176", "177", "178", "179", 
"180", "181", "182", "183", "184", "185", "186", "187", "188", "189", "190", "191", "192", "193", "194", 
"195", "196", "197", "198", "199", "200", "201", "202", "203", "204", "205", "206", "207", "208", "209", 
"210", "211", "212", "213", "214", "215", "216", "217", "218", "219", "220", "221", "222", "223", "224", 
"225", "226", "227", "228", "229", "230", "231", "232", "233", "234", "235", "236", "237", "238", "239", 
"240", "241", "242", "243", "244", "245", "246", "247", "248", "249", "250", "251", "252", "253", "254", 
"255"};

//---------------------------------------------------------
#include <cstdlib> // rand()
float randF() {
    return (double)rand() / ((double)RAND_MAX + 1);
}

//---------------------------------------------------------
Maths::Vec3 randomInUnitSphere() {
    Maths::Vec3 p;
    do {
        Maths::Vec3 randVec(randF(),randF(), randF());
        p = 2.0 * randVec - Maths::Vec3(1,1,1);
    } while(Maths::length2(p) >= 1.0f);
    return p;
}

//---------------------------------------------------------
Maths::Vec3 colourDiffuse(Ray const r,  Scene const & world) {
    HitRecord record;

    if(world.hit(r, 0.001f, std::numeric_limits<float>::max(), record)) {
        Maths::Vec3 target = record.point + record.normal + randomInUnitSphere();
        return 0.5f * colourDiffuse( Ray(record.point, target - record.point), world);
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
    world.addSphere(Maths::Vec3(0, -100.5, -1), 100);
    world.addSphere(Maths::Vec3(0, 0, -1), 0.5);

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
                auto u = float{(float)(i + ::randF()) / (float)(width)};
                auto v = float{(float)(j + ::randF()) / (float)(height)};
                Ray ray(cam.getRay(u, v));
                col += ::colourDiffuse(ray, world);

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
    
            buffer += lookup[ir] + " " + lookup[ig] + " " + lookup[ib] + "\n";
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
