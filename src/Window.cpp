#include "Window.hpp"


Window::Window(std::string const & title, int width, int height) :
    m_title(title)
,   m_x(-1)
,   m_y(-1)
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

    m_window = SDL_CreateWindow(title.c_str(), m_x, m_y, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
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

Window::Window(std::string const & title, int x, int y, int width, int height) :
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

    m_window = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
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

Window::~Window() {
    //@todo delete texture
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}

void
Window::eventLoop(bool & running) {
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