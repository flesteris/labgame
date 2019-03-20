#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include "rect.hpp"

// Klase realizuojanti teksturos funkcionaluma
class Image
{
private:
    SDL_Texture* texture;

public:
    //SDL_Renderer* ren;
    Image();
    ~Image();
    void draw(SDL_Renderer* ren, const Rect& srect, const Rect& drect);
    void loadBMP(SDL_Renderer* ren, const std::string filename);
};

#endif
