#ifndef TRACER_HPP
#define TRACER_HPP

// own
#include "Scene.hpp"
#include "Ray.hpp"
#include "Camera.hpp"
#include "Utils.hpp"

// djc_math
#include "djc_math/Vec3.hpp"

// std
#include <vector>
#include <cassert>

namespace globals {
    constexpr int rayDepth = 50;
}

//---------------------------------------------------------
djc_math::Vec3f fireRay(Ray const r,  Scene const & world, int depth) {
    HitRecord record;

    if(world.hit(r, 0.001f, std::numeric_limits<float>::max(), record)) {
        assert(record.ptr_mat != nullptr);
        Ray scattered;
        djc_math::Vec3f attenuation;

        if(depth < globals::rayDepth && record.ptr_mat->scatter(r, record, /*out var*/ attenuation, /*out var*/ scattered)) {
            return attenuation * fireRay(scattered, world, depth + 1);
        } else {
            return djc_math::Vec3f(0, 0, 0);
        }
    } else { 
        // background colour
        djc_math::Vec3f unitDircetion = djc_math::normalise(r.direction());
        auto t = 0.5f * (unitDircetion.y + 1.0f);
        return (1.0f - t) * djc_math::Vec3f(1.0f, 1.0f, 1.0f) + t * djc_math::Vec3f(0.5f, 0.7f, 1.0f);
    }
}

class TraceTaskRange final {
public:
    TraceTaskRange(int _xBegin, int _xEnd, int _yBegin, int _yEnd)
    :   xBegin(_xBegin)
    ,   xEnd(_xEnd)
    ,   yBegin(_yBegin)
    ,   yEnd(_yEnd){}

    int xBegin;
    int xEnd;
    int yBegin;
    int yEnd;
};

/*
    - number of samples
    - scene data
    - camera
    - if still running ?
*/

class TraceTask final {
public:
    TraceTask(TraceTaskRange range, int numSamples, Scene const & scene, Camera camera, int screenWidth, int screenHeight)
    :   m_range(range) 
    ,   m_numSamples(numSamples)
    ,   m_scene(scene)
    ,   m_camera(camera)
    ,   m_screenWidth(screenWidth)
    ,   m_screenHeight(screenHeight)
    {

        // std::cout << m_range.xBegin << "\n";
        // std::cout << m_range.xEnd << "\n";
        // std::cout << m_range.yBegin << "\n";
        // std::cout << m_range.yEnd << "\n";

        int jobWidth {m_range.xEnd - m_range.xBegin};
        int jobHeight {m_range.yEnd - m_range.yBegin};

        // std::cout << jobWidth << "\n";
        // std::cout << jobHeight << "\n";

        m_jobPixels.resize(jobHeight);
        for (int i = 0; i < jobHeight; i++) {
            m_jobPixels[i].resize(jobWidth);
        }
        
    }

    std::vector<std::vector<djc_math::Vec3f>> operator () () {

        for (auto s = 0; s < m_numSamples; s++) {
		    for( auto y = m_range.yBegin; y < m_range.yEnd; y++) { 
                for (auto x = m_range.xBegin; x < m_range.xEnd; x++) {     

		            auto u = static_cast<float>( (x + Utils::randF()) / (float)(m_screenWidth) );
                    auto v = static_cast<float>( (y + Utils::randF()) / (float)(m_screenHeight) ); // need to pass int width and heigh

                    Ray ray(m_camera.getRay(u, v));

                    m_jobPixels[y - m_range.yBegin][x - m_range.xBegin] += ::fireRay(ray, m_scene, 0); // needs offsets
                }
            }
        }

        return m_jobPixels;
    };

private:
    std::vector<std::vector<djc_math::Vec3f>> m_jobPixels;
    TraceTaskRange m_range;
    int m_numSamples;
    Scene const & m_scene; // each thread needs its own copy of scene? even tho its read only ?
    Camera m_camera;
    int m_screenWidth;
    int m_screenHeight;
};

#endif /* TRACER_HPP */