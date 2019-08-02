#include "images.hpp"

Images::Images(Game* game) : game(game)
{
    create_images();
    load_images();
}

Images::~Images()
{
    for(int i = 0; i < TILE_IMAGE_COUNT; ++i)
    {
        delete tiles[i];
    }

    for(int i = 0; i < HERO_IMAGE_COUNT; ++i)
    {
        delete hero_images[i];
    }

    for(int i = 0; i < UI_IMAGE_COUNT; ++i)
    {
        delete ui[i];
    }

    for(int i = 0; i < MONSTER_IMAGE_COUNT; ++i)
    {
        delete monster_images[i];
    }

    for(int i = 0; i < OBSTACLE_IMAGE_COUNT; ++i)
    {
        delete obstacle_images[i];
    }

    for(int i = 0; i < RESOURCE_IMAGE_COUNT; ++i)
    {
        delete resource_images[i];
    }

    delete transparent_tile;
    delete town_image;
}

void Images::create_images()
{
    for(int i = 0; i < TILE_IMAGE_COUNT; ++i)
    {
        tiles.push_back(new Image(game));
    }

    for(int i = 0; i < HERO_IMAGE_COUNT; ++i)
    {
        hero_images.push_back(new Image(game));
    }

    for(int i = 0; i < UI_IMAGE_COUNT; ++i)
    {
        ui.push_back(new Image(game));
    }

    for(int i = 0; i < MONSTER_IMAGE_COUNT; ++i)
    {
        monster_images.push_back(new Image(game));
    }

    for(int i = 0; i < OBSTACLE_IMAGE_COUNT; ++i)
    {
        obstacle_images.push_back(new Image(game));
    }

    for(int i = 0; i < RESOURCE_IMAGE_COUNT; ++i)
    {
        resource_images.push_back(new Image(game));
    }

    transparent_tile = new Image(game);
    town_image = new Image(game);
}

void Images::load_images()
{
    tiles[GRASS_TILE_1]->loadBMP("images//map_tiles//grass_tile_1.bmp");
    tiles[GRASS_TILE_2]->loadBMP("images//map_tiles//grass_tile_2.bmp");
    tiles[GRASS_TILE_3]->loadBMP("images//map_tiles//grass_tile_3.bmp");
    tiles[GRASS_TILE_4]->loadBMP("images//map_tiles//grass_tile_4.bmp");
    tiles[GRASS_TILE_5]->loadBMP("images//map_tiles//grass_tile_5.bmp");
    tiles[GRASS_TILE_6]->loadBMP("images//map_tiles//grass_tile_6.bmp");
    tiles[OFF_MAP_TILE]->loadBMP("images//map_tiles//off_map_tile.bmp");

    hero_images[SOUTHWEST]->loadBMP("images//hero//hero_southwest.bmp");
    hero_images[SOUTH]->loadBMP("images//hero//hero_south.bmp");
    hero_images[SOUTHEAST]->loadBMP("images//hero//hero_southeast.bmp");
    hero_images[EAST]->loadBMP("images//hero//hero_east.bmp");
    hero_images[NORTHEAST]->loadBMP("images//hero//hero_northeast.bmp");
    hero_images[NORTH]->loadBMP("images//hero//hero_north.bmp");
    hero_images[NORTHWEST]->loadBMP("images//hero//hero_northwest.bmp");
    hero_images[WEST]->loadBMP("images//hero//hero_west.bmp");

    ui[RIGHT_PANEL]->loadBMP("images//ui//right_panel.bmp");
    ui[BOTTOM_BAR]->loadBMP("images//ui//bottom_bar.bmp");
    ui[HOURGLASS]->loadBMP("images//ui//hourglass.bmp");
    ui[HOURGLASS_PRESSED]->loadBMP("images//ui//hourglass_pressed.bmp");
    ui[DESTINATION_MARK]->loadBMP("images//ui//destination_mark.bmp");
    ui[DESTINATION_MARK_EMPTY]->loadBMP("images//ui//destination_mark_empty.bmp");
    ui[DESTINATION_DOT]->loadBMP("images//ui//destination_dot.bmp");
    ui[DESTINATION_DOT_EMPTY]->loadBMP("images//ui//destination_dot_empty.bmp");

    monster_images[WOLF]->loadBMP("images//monsters//wolf.bmp");
    monster_images[GOBLIN]->loadBMP("images//monsters//goblin.bmp");
    monster_images[SNAKE]->loadBMP("images//monsters//snake.bmp");

    obstacle_images[FOREST_1]->loadBMP("images//hills&forests//forest_1.bmp");
    obstacle_images[HILLS_1]->loadBMP("images//hills&forests//hills_1.bmp");
    obstacle_images[HILLS_2]->loadBMP("images//hills&forests//hills_2.bmp");

    resource_images[GOLD]->loadBMP("images//resources//gold.bmp");
    resource_images[MERCURY_CRYSTAL]->loadBMP("images//resources//mercury_crystal.bmp");
    resource_images[SULPHUR_CRYSTAL]->loadBMP("images//resources//sulphur_crystal.bmp");
    resource_images[LIGHTNING_CRYSTAL]->loadBMP("images//resources//lightning_crystal.bmp");

    transparent_tile->loadBMP("images//transparent_tile.bmp");
    town_image->loadBMP("images//town//town.bmp");
}
