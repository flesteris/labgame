#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <SDL2/SDL.h>
#include <iostream>

#include "game.hpp"
#include "rect.hpp"

class Game;

class Image
{
private:
    SDL_Texture* texture;
    Game* game;

public:
    Image(Game* game);
    ~Image();

    void draw(const Rect &srect, const Rect &drect);
    void loadBMP(const std::string &filename);

    friend class WindowBox;
};

#endif
