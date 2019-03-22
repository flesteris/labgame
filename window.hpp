#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>

class Window
{
private:

public:
    SDL_Window *win;
    SDL_Renderer *ren;

    Window();
    ~Window();

    void create_window();
};

#endif
