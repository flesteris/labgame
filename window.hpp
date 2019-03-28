#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>
#include <iostream>

enum WindowDimensions
{
    WINDOW_WIDTH = 1280,
    WINDOW_HEIGTH = 720,
    WINDOW_CENTER_TILE_X = 460,
    WINDOW_CENTER_TILE_Y = 320
};

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
