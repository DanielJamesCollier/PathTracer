#ifndef Window_hpp
#define Window_hpp

// std
#include <fstream>
#include <string>

#if defined(_WIN32)
#   include "../build/Windows/deps/SDL2/include/SDL.h"
#elif defined(__APPLE__)
#   include "../build/Mac/deps/SDL2.framework/Versions/A/Headers/SDL.h"
#else
#   error "system not supported"
#endif

#include "MultiArray.hpp"

class Window final {
public:
    Window(std::string const & title, int x, int y, int width, int height) :
        m_title(title)
    ,   m_x(x)
    ,   m_y(y)
    ,   m_width(width)
    ,   m_height(height) 
    ,   m_pixels(width * height * 4, 0)
    {
        // init SDL and create window
        //---------------------------------------------------------
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
            std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
            exit(-1);
        }

        m_window = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_SHOWN);
        if (m_window == nullptr) {
            std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            exit(-1);
        }

        // create renderer
        //---------------------------------------------------------
        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (m_renderer == nullptr) {
            SDL_DestroyWindow(m_window);
            std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            exit(-1);
        }

        // create render buffer
        //---------------------------------------------------------
        m_renderTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, m_width, m_height);

        if(m_renderTexture == nullptr) {
            SDL_DestroyRenderer(m_renderer);
            SDL_DestroyWindow(m_window);
            std::cout << "Render Buffer Could not be created" << std::endl;
            SDL_Quit();
            exit(-1);
        }

        // clear the buffer to black
        //---------------------------------------------------------
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(m_renderer);
        SDL_RenderPresent(m_renderer);
    }

    ~Window() {
        //@todo delete texture
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
    }

    void eventLoop(bool & running) {
        /* Check for new events */
        while(SDL_PollEvent(&m_event))
        {
            /* If a quit event has been sent */
            if (m_event.type == SDL_QUIT)
            {
                /* Quit the application */
                running = false;
                SDL_Quit();
            }
        }
    }

    template<int width, int height>
    void draw(MultiArray<Maths::Vec3, width, height> & pixels, int numSamples) {
        
        auto index = 0;
        for (auto y = height - 1; y > 0; y--) { 
            for (auto x = 0; x < width; x++) {  
                Maths::Vec3 pixel = pixels(y, x);
                pixel /= static_cast<float>(numSamples);
                pixel = Maths::Vec3(sqrtf(pixel.getX()), sqrtf(pixel.getY()), sqrtf(pixel.getZ()));
            
                unsigned char r = static_cast<unsigned char>(255.99 * pixel.getX());
                unsigned char g = static_cast<unsigned char>(255.99 * pixel.getY());
                unsigned char b = static_cast<unsigned char>(255.99 * pixel.getZ());

                m_pixels[index + 0] = b; // blue ?
                m_pixels[index + 1] = g; // green
                m_pixels[index + 2] = r; // red
                m_pixels[index + 3] = SDL_ALPHA_OPAQUE;
                index+=4;
            }
        }


        int error = SDL_UpdateTexture(m_renderTexture, NULL, &m_pixels[0], width * 4);
        SDL_RenderCopy( m_renderer, m_renderTexture, NULL, NULL );
        SDL_RenderPresent(m_renderer);
    }

//TODO: reorder
private:
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
};

#endif /* Window_hpp */