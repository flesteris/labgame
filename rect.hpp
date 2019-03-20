#ifndef RECT_HPP
#define RECT_HPP

#include <SDL2/SDL.h>

class Rect
{
private:

public:
    int x, y, w, h;
    Rect();
    Rect(int upper_left_x, int upper_left_y, int width, int height);
    SDL_Rect to_sdl_rect() const;
    bool is_empty() const;
    ~Rect();
};

#endif
