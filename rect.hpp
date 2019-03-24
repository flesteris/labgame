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
    Rect(Pos upper_left_point, int width, int height);
    SDL_Rect to_sdl_rect() const;
    bool is_empty() const;
};

#endif
