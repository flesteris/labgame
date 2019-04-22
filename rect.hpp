#ifndef RECT_HPP
#define RECT_HPP

#include <SDL2/SDL.h>

#include "pos.hpp"

class Pos;

class Rect
{
public:
    Pos* pos;
    int w, h;

    Rect();
    Rect(Pos upper_left_point, int width, int height);
    Rect(Pos upper_left_point, Pos lower_right_point);
    Rect(int upper_left_x, int upper_left_y, int width, int height);

    Rect expand(int x, int y) const;
    SDL_Rect to_sdl_rect() const;
    bool is_empty() const;
};

#endif
