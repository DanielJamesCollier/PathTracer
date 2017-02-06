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

        // clear the buffer to black
        //---------------------------------------------------------
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
        SDL_RenderClear(m_renderer);
        SDL_RenderPresent(m_renderer);
    }

    ~Window() {
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
    
    void output(int r, int g, int b, int x, int y) {
        SDL_SetRenderDrawColor(m_renderer, r, g, b, 255);
        SDL_RenderDrawPoint(m_renderer, x, y); 
    }

    template<int width, int height>
    void draw(MultiArray<Maths::Vec3, width, height> & pixels, int numSamples) {
        int forward = 0;
        for(auto j = height; j > 0; j--) {
            forward++;
                for(auto i = 0; i < width; i++) {

                Maths::Vec3 colour = pixels(i,j);

                colour /= static_cast<float>(numSamples);
                colour = Maths::Vec3(sqrtf(colour.getX()), sqrtf(colour.getY()), sqrtf(colour.getZ()));
                int ir = static_cast<int>(255.99 * colour.getX());
                int ig = static_cast<int>(255.99 * colour.getY());
                int ib = static_cast<int>(255.99 * colour.getZ());
        
                SDL_SetRenderDrawColor(m_renderer, ir, ig, ib, 255);
                SDL_RenderDrawPoint(m_renderer, i, forward); 
            }
        }

        swapBackBuffer();
    }

    void swapBackBuffer() {
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
};

#endif /* Window_hpp */