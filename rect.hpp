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
    Rect(const Pos &upper_left_point, int width, int height);
    Rect(const Pos &upper_left_point, const Pos &lower_right_point);
    Rect(int upper_left_x, int upper_left_y, int width, int height);

    Rect expand(int x, int y) const;
    Rect expand(int x_to_the_left, int y_upwards, int x_to_the_right, int y_downwards) const;
    SDL_Rect to_sdl_rect() const;
    bool is_empty() const;
};

#endif
