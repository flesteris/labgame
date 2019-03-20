#ifndef IMAGES_HPP
#define IMAGES_HPP

#include "image.hpp"
#include "game.hpp"
#include <iostream>
#include <SDL2/SDL.h>

enum TileType
{
    GRASS_TILE_1 = 0,
    GRASS_TILE_2 = 1,
    GRASS_TILE_3 = 2,
    GRASS_TILE_4 = 3,
    GRASS_TILE_5 = 4,
    GRASS_TILE_6 = 5,
    OFF_MAP_TILE = 6
};

enum HeroDirection
{
    SOUTHWEST = 0,
    SOUTH = 1,
    SOUTHEAST = 2,
    EAST = 3,
    NORTHEAST = 4,
    NORTH = 5,
    NORTHWEST = 6,
    WEST = 7,
    NO_DIRECTION = 8
};

enum UI
{
    RIGHT_PANEL = 0,
    BOTTOM_BAR = 1,
    HOURGLASS = 2,
    NO_MOVEMENT_POINTS = 3,
    DESTINATION = 4
};

class Images
{
private:

public:
    Image tiles[7];
    Image hero_images[8];
    Image ui[5];
    SDL_Renderer* ren;
    Images();
    Images(SDL_Renderer* ren);
    ~Images();
    void load_images();
};

#endif
