#ifndef IMAGES_HPP
#define IMAGES_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "image.hpp"
#include "game.hpp"

enum TileType
{
    GRASS_TILE_1 = 0,
    GRASS_TILE_2 = 1,
    GRASS_TILE_3 = 2,
    GRASS_TILE_4 = 3,
    GRASS_TILE_5 = 4,
    GRASS_TILE_6 = 5,
    OFF_MAP_TILE = 6,
    TILE_IMAGE_COUNT = 7
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
    HERO_IMAGE_COUNT = 8,
    NO_DIRECTION = 8
};

enum UI
{
    RIGHT_PANEL = 0,
    BOTTOM_BAR = 1,
    HOURGLASS = 2,
    NO_MOVEMENT_POINTS = 3,
    DESTINATION = 4,
    UI_IMAGE_COUNT = 5
};

class Game;
class Image;

class Images
{
private:

public:
    Game* game;
    std::vector<Image*> tiles;
    std::vector<Image*> hero_images;
    std::vector<Image*> ui;

    Images(Game* game);
    ~Images();
    void load_images();
};

#endif
