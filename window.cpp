#include "window.hpp"

Window::Window()
{
    create_window();
}

Window::~Window()
{
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
}

void Window::create_window()
{
    win = SDL_CreateWindow("Spicy boi", 320, 180, WINDOW_WIDTH, WINDOW_HEIGTH, SDL_WINDOW_SHOWN);
    if(!win)
    {
        throw SDL_window_error();
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!ren)
    {
        SDL_DestroyWindow(win);
        throw SDL_renderer_error();
    }

    SDL_RaiseWindow(win);
    SDL_SetWindowGrab(win, SDL_TRUE);
}
