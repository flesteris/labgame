#ifndef CURSOR_IMAGE_HPP
#define CURSOR_IMAGE_HPP

#include <iostream>
#include <SDL2/SDL.h>

#include "exceptions.hpp"

class CursorImage
{
public:
    SDL_Surface* surface;

    CursorImage();
    ~CursorImage();

    void loadBMP(const std::string &filename);
};

#endif
