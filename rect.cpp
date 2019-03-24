#include "rect.hpp"
#include <SDL2/SDL.h>

Rect::Rect() : pos(0, 0), w(0), h(0)
{

}

Rect::Rect(Pos upper_left_point, int width, int height) : pos(upper_left_point), w(width), h(height)
{

}

SDL_Rect Rect::to_sdl_rect() const
{
    SDL_Rect sdlrect = {pos.x, pos.y, w, h};
    return sdlrect;
}

bool Rect::is_empty() const
{
    return w == 0 && h == 0;
}
