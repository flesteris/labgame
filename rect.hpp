#ifndef RECT_HPP
#define RECT_HPP

#include <SDL2/SDL.h>
#include "pos.hpp"

class Rect
{
private:

public:
    Pos pos;
    int w, h;
    Rect();
    Rect(Pos upper_left_point, Pos lower_right_point);
    Rect(Pos upper_left_point, int width, int height);
    Rect(int upper_left_x, int upper_left_y, int width, int height);
    SDL_Rect to_sdl_rect() const;
    bool is_empty() const;
};

#endif
