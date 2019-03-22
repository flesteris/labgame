#include "rect.hpp"
#include <SDL2/SDL.h>

Rect::Rect() : x(0), y(0), w(0), h(0)
{

}

Rect::Rect(int upper_left_x, int upper_left_y, int width, int height) : x(upper_left_x), y(upper_left_y), w(width), h(height)
{

}

SDL_Rect Rect::to_sdl_rect() const
{
    SDL_Rect sdlrect = {x, y, w, h};
    return sdlrect;
}

bool Rect::is_empty() const
{
    return w == 0 && h == 0;
}
