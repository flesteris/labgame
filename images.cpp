#include "images.hpp"

Images::Images(SDL_Renderer* ren) : ren(ren)
{

}

Images::~Images()
{

}

void Images::load_images()
{
    tiles[GRASS_TILE_1].loadBMP(ren, "images//map_tiles//grass_tile_1.bmp");
    tiles[GRASS_TILE_2].loadBMP(ren, "images//map_tiles//grass_tile_2.bmp");
    tiles[GRASS_TILE_3].loadBMP(ren, "images//map_tiles//grass_tile_3.bmp");
    tiles[GRASS_TILE_4].loadBMP(ren, "images//map_tiles//grass_tile_4.bmp");
    tiles[GRASS_TILE_5].loadBMP(ren, "images//map_tiles//grass_tile_5.bmp");
    tiles[GRASS_TILE_6].loadBMP(ren, "images//map_tiles//grass_tile_6.bmp");
    tiles[OFF_MAP_TILE].loadBMP(ren, "images//map_tiles//off_map_tile.bmp");

    hero_images[SOUTHWEST].loadBMP(ren, "images//hero_southwest.bmp");
    hero_images[SOUTH].loadBMP(ren, "images//hero_south.bmp");
    hero_images[SOUTHEAST].loadBMP(ren, "images//hero_southeast.bmp");
    hero_images[EAST].loadBMP(ren, "images//hero_east.bmp");
    hero_images[NORTHEAST].loadBMP(ren, "images//hero_northeast.bmp");
    hero_images[NORTH].loadBMP(ren, "images//hero_north.bmp");
    hero_images[NORTHWEST].loadBMP(ren, "images//hero_northwest.bmp");
    hero_images[WEST].loadBMP(ren, "images//hero_west.bmp");

    ui[RIGHT_PANEL].loadBMP(ren, "images//right_panel.bmp");
    ui[BOTTOM_BAR].loadBMP(ren, "images//bottom_bar.bmp");
    ui[HOURGLASS].loadBMP(ren, "images//hourglass.bmp");
    ui[NO_MOVEMENT_POINTS].loadBMP(ren, "images//out_of_movement_points.bmp");
    ui[DESTINATION].loadBMP(ren, "images//destination.bmp");
}
