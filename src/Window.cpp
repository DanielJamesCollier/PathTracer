#include "Window.hpp"


Window::Window(std::string const & title, int width, int height) 
:   m_x(-1)
,   m_y(-1)
,   m_width(width)
,   m_height(height) 
,   m_pixels(width * height * 4, 0)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        exit(-1);
    }

    if (SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI, &m_window, &m_renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
        exit(-1);
     }

    // create render buffer
    m_renderTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, m_width, m_height);

    if(m_renderTexture == nullptr) {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        std::cout << "Render Buffer Could not be created" << std::endl;
        SDL_Quit();
        exit(-1);
    }

    // set the screen the black
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_renderer);
    SDL_RenderPresent(m_renderer);
}

Window::~Window() {
    //@todo delete texture
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}

void
Window::eventLoop(bool & running) {
    /* Check for new events */
    while (SDL_PollEvent(&m_event)) {
        /* If a quit event has been sent */
        if (m_event.type == SDL_QUIT) {
            /* Quit the application */
            running = false;
            SDL_Quit();
        }
    }
}