#ifndef Window_hpp
#define Window_hpp

// djc_math
#include "djc_math/Vec3.hpp"

// dependancies
#include "SDL2/SDL.h"

// std
#include <string>
#include <fstream>
#include <array>
#include <vector>


class SDL_Module final {

    int m_width;
    int m_height;
    int m_x;
    int m_y;
    SDL_Window * m_window;
    SDL_Renderer * m_renderer;
    SDL_Event m_event;
    SDL_Texture * m_renderTexture;
    std::vector<unsigned char> m_pixels;

public:
    SDL_Module(std::string const & title, int width, int height);
    ~SDL_Module();

    void eventLoop(bool & running);
    void draw(std::vector<std::vector<djc_math::Vec3f>> const & pixels, int numSamples);

};

#endif /* Window_hpp */