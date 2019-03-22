#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include "rect.hpp"
#include "game.hpp"

class Game;

class Image
{
private:
    SDL_Texture* texture;

public:
    Game* game;
    Image(Game* game);
    ~Image();
    void draw(const Rect& srect, const Rect& drect);
    void loadBMP(const std::string filename);
};

#endif