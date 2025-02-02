#include "graphics.hpp"

SDL_Window* Graphics::m_window{nullptr};

void Graphics::init() {
    SDL_Init(SDL_INIT_VIDEO);
    m_window = SDL_CreateWindow("nashira2", 0, 0, 0);
}

/// Changes the window size and centralizes the window
void Graphics::set_window_size(const int width, const int height)
{
    SDL_SetWindowSize(m_window, width, height);
    SDL_SetWindowPosition(m_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void Graphics::quit()
{
    SDL_DestroyWindow(m_window);
}