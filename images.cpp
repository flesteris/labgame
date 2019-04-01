#include "images.hpp"

Images::Images(Game* game) : game(game)
{
    load_images();
}

Images::~Images()
{

}

void Images::load_images()
{
    for (int i = 0; i < TILE_IMAGE_COUNT; ++i)
    {
        tiles.push_back(new Image(game));
    }

    for (int i = 0; i < HERO_IMAGE_COUNT; ++i)
    {
        hero_images.push_back(new Image(game));
    }

    for (int i = 0; i < UI_IMAGE_COUNT; ++i)
    {
        ui.push_back(new Image(game));
    }

    for (int i = 0; i < MONSTER_IMAGE_COUNT; ++i)
    {
        monster_images.push_back(new Image(game));
    }

    tiles[GRASS_TILE_1]->loadBMP("images//map_tiles//grass_tile_1.bmp");
    tiles[GRASS_TILE_2]->loadBMP("images//map_tiles//grass_tile_2.bmp");
    tiles[GRASS_TILE_3]->loadBMP("images//map_tiles//grass_tile_3.bmp");
    tiles[GRASS_TILE_4]->loadBMP("images//map_tiles//grass_tile_4.bmp");
    tiles[GRASS_TILE_5]->loadBMP("images//map_tiles//grass_tile_5.bmp");
    tiles[GRASS_TILE_6]->loadBMP("images//map_tiles//grass_tile_6.bmp");
    tiles[OFF_MAP_TILE]->loadBMP("images//map_tiles//off_map_tile.bmp");

    hero_images[SOUTHWEST]->loadBMP("images//hero_southwest.bmp");
    hero_images[SOUTH]->loadBMP("images//hero_south.bmp");
    hero_images[SOUTHEAST]->loadBMP("images//hero_southeast.bmp");
    hero_images[EAST]->loadBMP("images//hero_east.bmp");
    hero_images[NORTHEAST]->loadBMP("images//hero_northeast.bmp");
    hero_images[NORTH]->loadBMP("images//hero_north.bmp");
    hero_images[NORTHWEST]->loadBMP("images//hero_northwest.bmp");
    hero_images[WEST]->loadBMP("images//hero_west.bmp");

    ui[RIGHT_PANEL]->loadBMP("images//right_panel.bmp");
    ui[BOTTOM_BAR]->loadBMP("images//bottom_bar.bmp");
    ui[HOURGLASS]->loadBMP("images//hourglass.bmp");
    ui[HOURGLASS_PRESSED]->loadBMP("images//hourglass_pressed.bmp");
    ui[NO_MOVEMENT_POINTS]->loadBMP("images//out_of_movement_points.bmp");
    ui[DESTINATION_MARK]->loadBMP("images//destination_mark.bmp");
    ui[DESTINATION_MARK_EMPTY]->loadBMP("images//destination_mark_empty.bmp");
    ui[DESTINATION_DOT]->loadBMP("images//destination_dot.bmp");
    ui[DESTINATION_DOT_EMPTY]->loadBMP("images//destination_dot_empty.bmp");

    monster_images[WOLF]->loadBMP("images//monsters//wolf.bmp");
    monster_images[GOBLIN]->loadBMP("images//monsters//goblin.bmp");
    monster_images[SNAKE]->loadBMP("images//monsters//snake.bmp");
}
