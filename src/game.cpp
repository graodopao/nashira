#include "game.hpp"
#include <SDL3/SDL_events.h>

void Game::run()
{
    while (!m_should_quit)
    {
        pool_events();
    }
}

void Game::pool_events()
{
    SDL_Event event{};
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_EVENT_QUIT:
                m_should_quit = true;
                break;
            default: break;
        }
    }
}
