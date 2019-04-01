#include "rect.hpp"

Rect::Rect() : pos(new Pos(0, 0)), w(0), h(0)
{

}

Rect::Rect(Pos upper_left_point, int width, int height) : pos(new Pos(upper_left_point.x, upper_left_point.y)), w(width), h(height)
{

}

Rect::Rect(int upper_left_x, int upper_left_y, int width, int height) : pos(new Pos(upper_left_x, upper_left_y)), w(width), h(height)
{

}

SDL_Rect Rect::to_sdl_rect() const
{
    SDL_Rect sdlrect = {pos->x, pos->y, w, h};
    return sdlrect;
}

bool Rect::is_empty() const
{
    return w == 0 && h == 0;
}
