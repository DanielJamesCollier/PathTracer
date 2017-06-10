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
    ~Window();

    void eventLoop(bool & running);

    template<size_t WIDTH, size_t HEIGHT>
    void draw(Array2D<djc_math::Vec3f, WIDTH, HEIGHT> & pixels, int numSamples) {

        /*
        - convert data from a Array2D<djc_math::Vec3f, WIDTH, HEIGHT> & pixels to  std::vector<unsigned char>;
        - map the pixels from range(0.0f - 1.0f) to range(0 - 255)
        - the std::vector<unsigned char> also stores an alpha channel
        */

        auto index = 0;
        for (auto y = 0; y < HEIGHT; y++) { 
            for (auto x = 0; x < WIDTH; x++) {  
                djc_math::Vec3f pixel = pixels[y][x];
                pixel /= static_cast<float>(numSamples);
                pixel = djc_math::Vec3f(sqrtf(pixel.x), sqrtf(pixel.y), sqrtf(pixel.z));
            
                m_pixels[index + 0] = static_cast<unsigned char>(255.99 * pixel.z); // blue 
                m_pixels[index + 1] = static_cast<unsigned char>(255.99 * pixel.y); // green
                m_pixels[index + 2] = static_cast<unsigned char>(255.99 * pixel.x); // red
                m_pixels[index + 3] = SDL_ALPHA_OPAQUE;
                index+=4;
            }
        }

        /*
         - update a texture with m_pixels
         - copy the texture contexts into the renderer
         - push the renderer with its new pixels to the screen
        */
        int error = SDL_UpdateTexture(m_renderTexture, NULL, &m_pixels[0], WIDTH * 4);
        SDL_RenderCopyEx(m_renderer, m_renderTexture, NULL, NULL, 0, NULL, SDL_FLIP_VERTICAL);
        SDL_RenderPresent(m_renderer);
    }
};

#endif /* Window_hpp */