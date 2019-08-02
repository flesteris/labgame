#ifndef IMAGES_HPP
#define IMAGES_HPP

#include <SDL2/SDL.h>
#include <vector>

#include "game.hpp"
#include "image.hpp"

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

enum MonsterType
{
    WOLF = 0,
    GOBLIN = 1,
    SNAKE = 2,
    MONSTER_IMAGE_COUNT = 3
};

enum ObstacleType
{
    FOREST_1 = 0,
    HILLS_1 = 1,
    HILLS_2 = 2,
    OBSTACLE_IMAGE_COUNT = 3
};

enum ResourceType
{
    GOLD = 0,
    MERCURY_CRYSTAL = 1,
    SULPHUR_CRYSTAL = 2,
    LIGHTNING_CRYSTAL = 3,
    RESOURCE_IMAGE_COUNT = 4
};

enum UI
{
    RIGHT_PANEL = 0,
    BOTTOM_BAR = 1,
    HOURGLASS = 2,
    HOURGLASS_PRESSED = 3,
    NO_MOVEMENT_POINTS = 4,
    DESTINATION_MARK = 5,
    DESTINATION_MARK_EMPTY = 6,
    DESTINATION_DOT = 7,
    DESTINATION_DOT_EMPTY = 8,
    UI_IMAGE_COUNT = 9
};

class Game;
class Image;

class Images
{
private:
    Game* game;

public:
    std::vector<Image*> tiles;
    std::vector<Image*> hero_images;
    std::vector<Image*> ui;
    std::vector<Image*> monster_images;
    std::vector<Image*> obstacle_images;
    std::vector<Image*> resource_images;
    Image* transparent_tile;
    Image* town_image;

    Images(Game* game);
    ~Images();

    void create_images();
    void load_images();
};

#endif
