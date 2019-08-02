#include "rect.hpp"

Rect::Rect() :
    pos(new Pos(0, 0)),
    w(0),
    h(0)
{

}

Rect::Rect(const Pos &upper_left_point, int width, int height) :
    pos(new Pos(upper_left_point.x, upper_left_point.y)),
    w(width),
    h(height)
{

}

Rect::Rect(const Pos &upper_left_point, const Pos &lower_right_point) :
    pos(new Pos(upper_left_point.x, upper_left_point.y)),
    w(lower_right_point.x - upper_left_point.x),
    h(lower_right_point.y - upper_left_point.y)
{

}

Rect::Rect(int upper_left_x, int upper_left_y, int width, int height) :
    pos(new Pos(upper_left_x, upper_left_y)),
    w(width),
    h(height)
{

}

Rect Rect::expand(int x, int y) const
{
    return Rect(pos->x - x, pos->y - y, w + 2 * x, h + 2 * y);
}

Rect Rect::expand(int x_to_the_left, int y_upwards, int x_to_the_right, int y_downwards) const
{
    return Rect(pos->x - x_to_the_left, pos->y - y_upwards, w + x_to_the_left + x_to_the_right, h + y_upwards + y_downwards);
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
