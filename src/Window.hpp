#ifndef Window_hpp
#define Window_hpp

// djc_math
#include "djc_math/Vec3.hpp"

// dependancies
#include "SDL2/SDL.h"

// std
#include <string>
#include <fstream>
#include <vector>

class Window final {

    std::string m_title;
    int m_width;
    int m_height;
    int m_x;
    int m_y;
    SDL_Window * m_window;
    SDL_Renderer * m_renderer;
    SDL_Event m_event;
    SDL_Texture * m_renderTexture;
    std::vector<unsigned char> m_pixels;

private: // aliases
    template<typename TYPE, size_t WIDTH, size_t HEIGHT>
    using Array2D = std::array<std::array<TYPE, WIDTH>, HEIGHT>;

public:
    Window(std::string const & title, int width, int height);
    Window(std::string const & title, int x, int y, int width, int height);
    ~Window();

    void eventLoop(bool & running);

    template<size_t WIDTH, size_t HEIGHT>
    void draw(Array2D<djc_math::Vec3f, WIDTH, HEIGHT> & pixels, int numSamples) {
        
        auto index = 0;

        for (auto y = HEIGHT - 1; y > 0; y--) { 
            for (auto x = 0; x < WIDTH; x++) {  
                djc_math::Vec3f pixel = pixels[y][x];
                pixel /= static_cast<float>(numSamples);
                pixel = djc_math::Vec3f(sqrtf(pixel.x), sqrtf(pixel.y), sqrtf(pixel.z));
            
                unsigned char r = static_cast<unsigned char>(255.99 * pixel.x);
                unsigned char g = static_cast<unsigned char>(255.99 * pixel.y);
                unsigned char b = static_cast<unsigned char>(255.99 * pixel.z);

                m_pixels[index + 0] = b; // blue 
                m_pixels[index + 1] = g; // green
                m_pixels[index + 2] = r; // red
                m_pixels[index + 3] = SDL_ALPHA_OPAQUE;
                index+=4;
            }
        }


        int error = SDL_UpdateTexture(m_renderTexture, NULL, &m_pixels[0], WIDTH * 4);
        SDL_RenderCopy( m_renderer, m_renderTexture, NULL, NULL );
        SDL_RenderPresent(m_renderer);
    }
};

#endif /* Window_hpp */