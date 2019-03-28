#ifndef CURSOR_HPP
#define CURSOR_HPP

#include <SDL2/SDL.h>
#include <vector>

enum CursorType
{
    SW_ARROW = 0,
    S_ARROW = 1,
    SE_ARROW = 2,
    E_ARROW = 3,
    NE_ARROW = 4,
    N_ARROW = 5,
    NW_ARROW = 6,
    W_ARROW = 7,
    NORMAL_CURSOR = 8,
    CURSOR_IMAGE_COUNT = 9
};

class Cursor
{
private:
    std::vector<SDL_Surface*> surfaces;
    SDL_Cursor *cursor;

public:
    Cursor();
    ~Cursor();
    void load_surfaces();
    void set_cursor(); /// gal ir nereik
    void set_cursor(int a);
};

#endif // CURSOR_HPP
