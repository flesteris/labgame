#include "window.hpp"
#include <iostream>

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
    win = SDL_CreateWindow("Spicy boi", 320, 180, 1280, 720, SDL_WINDOW_SHOWN);
    if (win == nullptr)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr)
    {
        SDL_DestroyWindow(win);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    }
}
