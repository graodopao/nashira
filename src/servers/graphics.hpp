#pragma once
#include <SDL3/SDL.h>

class Graphics {
public:
    static void init();
    static void quit();

    static void set_window_size(int width, int height);
private:
    static SDL_Window* m_window;
};
